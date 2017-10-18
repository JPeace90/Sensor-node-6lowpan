/*
 * for testing and debugging with emulator terminal look at readme.txt
 */


#include "contiki.h"
#include "lib/random.h"
#include "sys/ctimer.h"
#include "sys/etimer.h"
#include "sensors_settings.h"

#include "net/ip/uip.h"
#include "net/ipv6/uip-ds6.h"
#include "net/ip/uip-debug.h"
#include "net/ipv6/uip-nd6.h"

#include "time.h"

#include "simple-udp.h"
#include "servreg-hack.h"
#include "rpl-private.h"

#include "net/rpl/rpl.h"
#include "message.h"

#include <stdio.h>
#include <string.h>

/*------------------------------------------*/

#define DEBUG DEBUG_FULL
#define UPDATE_TIMER 10000 //periodic timer (ms): node send sensors values to border router
#define UDP_PORT_SEND 1234
#define UDP_PORT_REC 1235

#define SEND_INTERVAL		(CLOCK_SECOND)
#define SEND_TIME		(SEND_INTERVAL)//(random_rand() % (SEND_INTERVAL))
#define DELAY (random_rand() % (SEND_INTERVAL))

//compares the last 4 bit of an ipv6 address
#define ADDR_EQUAL(tmp, tmp2) (tmp2.u8[12]==tmp.u8[12] && tmp2.u8[13]==tmp.u8[13] && tmp2.u8[14]==tmp.u8[14] && tmp2.u8[15]==tmp.u8[15])

static struct simple_udp_connection unicast_connection;
int j = 0, sendBool = 0;
uint8_t *tmpdata;
int SEND_OPERATION=4;

/*---------------------------------------------------------------------------*/
PROCESS(unicast_sender_process, "Unicast sender example process");
/*---------------------------------------------------------------------------*/
AUTOSTART_PROCESSES(&unicast_sender_process);

//Callback function: sensor-node waits for an event
static void
receiver(struct simple_udp_connection *c,
		const uip_ipaddr_t *sender_addr,
		uint16_t sender_port,
		const uip_ipaddr_t *receiver_addr,
		uint16_t receiver_port,
		const our_message_t *data,
		uint16_t datalen)
{

	printf("------------------------- SENDER - receiver callback ------------------------\n\n");
	printf("Data received from: ");
	uip_debug_ipaddr_print(sender_addr);
	printf("\n");

	our_message_t incoming_message;

	incoming_message = *data;
	j = incoming_message.message_type;


	printf("Message_type: %d, Original_ip_address: ", incoming_message.message_type);
	uip_debug_ipaddr_print(&incoming_message.original_ip_address);
	printf("\n");

	process_post_synch(&unicast_sender_process, 0, &incoming_message);
	j = 0;

	printf("-----------------------------------------------------------------------------\n\n");

}
/*---------------------------------------------------------------------------*/
//this function assigns ipv6 addresses to network nodes
//ipv6 address: prefix + macaddress
static uip_ipaddr_t *
set_global_address(void)
{
	static uip_ipaddr_t ipaddr;
	int i;
	uint8_t state;

	uip_ip6addr(&ipaddr, UIP_DS6_DEFAULT_PREFIX, 0, 0, 0, 0, 0, 0, 0);
	uip_ds6_set_addr_iid(&ipaddr, &uip_lladdr);
	uip_ds6_addr_add(&ipaddr, 0, ADDR_AUTOCONF);

	printf("IPv6 addresses: ");
	for(i = 0; i < UIP_DS6_ADDR_NB; i++) {
		state = uip_ds6_if.addr_list[i].state;
		if(uip_ds6_if.addr_list[i].isused &&
				(state == ADDR_TENTATIVE || state == ADDR_PREFERRED)) {
			uip_debug_ipaddr_print(&uip_ds6_if.addr_list[i].ipaddr);
			printf("\n");
		}
	}

	return &ipaddr;
}

/*---------------------------------------------------------------------------*/
static void init_udp_connection(){
	simple_udp_register(&unicast_connection, UDP_PORT_SEND, NULL, UDP_PORT_SEND, receiver);
	printf("Init terminata\n");
}
//DOWNWARD COMMUNICATION: sensor-node send multicast messages to to its neighbors
static void children_multicast(our_message_t *message){
	static uip_ds6_route_t *r;
	uip_ipaddr_t neighbors_routes[UIP_DS6_ROUTE_NB];
	int i=0, count_neighbors=0, sent =1;
	memset(&neighbors_routes, 0, sizeof(neighbors_routes));

	PRINTF("Route entries:\n");
	message-> message_type=ROOT_GET_ALL;

	for(r = uip_ds6_route_head(); r != NULL; r = uip_ds6_route_next(r)){

		uip_ipaddr_t tmp = r->ipaddr;
		uip_ipaddr_t tmp2 = *uip_ds6_route_nexthop(r);

		if (ADDR_EQUAL(tmp, tmp2)) {

			for (i = 0; i < UIP_DS6_ROUTE_NB; i++) {
				if (ADDR_EQUAL(neighbors_routes[i], tmp)){
					sent = 0;
					break;
				}
			}

			if (sent != 0) {
				neighbors_routes[count_neighbors] = tmp;
				count_neighbors+=1;
				sent = 1;
			}
		}
	}

	for(i = 0; i < count_neighbors; i++) {
		simple_udp_sendto(&unicast_connection,
				&message,
				sizeof(our_message_t),
				&neighbors_routes[i]);
		uip_debug_ipaddr_print(&neighbors_routes[i]); printf("\n");
	}

	printf("Messaggi inviati a: %d figli\n", count_neighbors);
}

//function that returns sensor values
static void getSensorsValues(our_message_t *message){
	int32_t intPart, decPart;

	BSP_TEMPERATURE_Get_Temp(TEMPERATURE_handle, &temperature_value);
	SENSOR_PRINT(temperature_value, intPart, decPart);
	message->temperature.intPart=intPart;
	message->temperature.decPart=decPart;
	BSP_HUMIDITY_Get_Hum(HUMIDITY_handle, &humidity_value);
	SENSOR_PRINT(humidity_value, intPart, decPart);
	message->humidity.intPart=intPart;
	message->humidity.decPart=decPart;
	BSP_PRESSURE_Get_Press(PRESSURE_handle, &pressure_value);
	SENSOR_PRINT(pressure_value, intPart, decPart);
	message->pressure.intPart=intPart;
	message->pressure.decPart=decPart;
}


/*---------------------------------------------------------------------------*/
//when a message arrives in the callback function, control goes to this process
PROCESS_THREAD(unicast_sender_process, ev, data)
{
	static struct etimer update_timer;
	uip_ipaddr_t *addr;
	our_message_t *message_data;
	our_message_t message;
	rpl_dag_t *dag;
	uip_ipaddr_t *ipaddr;
	static int m_id = 0;
	int i = 0;

	PROCESS_BEGIN();

	printf("SENDER\n");

	servreg_hack_init();

	ipaddr = set_global_address();

	init_udp_connection();

	while(1) {
		etimer_set(&update_timer,UPDATE_TIMER);
		PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&update_timer));

		message_data = data;
		message = *message_data;

		extern uip_ds6_netif_t uip_ds6_if;
		dag = rpl_get_any_dag();

		if(etimer_expired(&update_timer))SEND_OPERATION=UPDATE;
		else SEND_OPERATION = message.message_type;

		printf("------------------------------ PROCESS SENDER ----------------------------\n\n");
		switch (SEND_OPERATION) {
		//GET_ALL: upon receipt of this message the node:
		//1 - forward the received message to the nodes in its sub tree
		//2-  send sensor values to the preferred parent (addr)
		case 1:
			m_id = m_id + 1;
			message.message_id = m_id;
			strcpy(message.name, "NODO1");

			message.message_type = SET_VALUE;
			getSensorsValues(&message);

			for ( i = 0; i < UIP_DS6_ADDR_NB; i += 1) {
				if ( uip_ds6_if.addr_list[i].isused) {
					message.original_ip_address = uip_ds6_if.addr_list[i].ipaddr;
				}
			}
#if DEBUG
			printf("Nome nodo: %s\n", message.name);
			printf(" | ID: %d | Temperature: %lu.%lu | Umidity: %lu.%lu | Pressure: %lu.%lu | Message type: %d\n",
					message.message_id,
					message.temperature.intPart,
					message.temperature.decPart,
					message.humidity.intPart,
					message.humidity.decPart,
					message.pressure.intPart,
					message.pressure.decPart,
					message.message_type);
#endif
			//takes the ipv6 address of the parent node
			addr = rpl_get_parent_ipaddr(dag->preferred_parent);
			//send sensor values to the preferred parent
			if (addr != NULL) simple_udp_sendto(&unicast_connection, &message, sizeof(message), addr);
			else printf("Indirizzo non valido\n");
			printf("Invio del messaggio al padre: "); uip_debug_ipaddr_print(addr); printf("\n");
			/* --------- */

			children_multicast(&message);

			break;
		case 2:
			//SET_VALUE: upon receipt of this message the node:
			//1- forward the received message to the preferred parent
			addr = rpl_get_parent_ipaddr(dag->preferred_parent);
			if (addr != NULL) simple_udp_sendto(&unicast_connection, &message, sizeof(message), addr);
			else printf("Indirizzo non valido\n");

			printf("Forward del messaggio ricevuto da: "); uip_debug_ipaddr_print(&message.original_ip_address); printf(" verso "); uip_debug_ipaddr_print(addr); printf("\n");
			break;
		case 3:
			//UPDATE: periodically after the time t expires (update_timer):
			//1- node sends sensors values to their parent

			printf("------- INVIO MESSAGGIO DI UPDATE ------\n");
			m_id = m_id + 1;
			message.message_id = m_id;
			strcpy(message.name, "NODO2");
			addr = rpl_get_parent_ipaddr(dag->preferred_parent);

			message.message_type = SET_VALUE;

			getSensorsValues(&message);

			message.final_ip_destination = dag->dag_id;

#if DEBUG
			printf("Indirizzo di destinazione: "); uip_debug_ipaddr_print(addr); printf("\n");
			printf("Nome nodo: %s\n", message.name);
			printf("Message type: %d\n", message.message_type);
			printf("ID: %d\n", message.message_id);
			printf("Temperature: %lu.%lu | Umidity: %lu.%lu | Pressure: %lu.%lu\n",
					message.temperature.intPart,
					message.temperature.decPart,
					message.humidity.intPart,
					message.humidity.decPart,
					message.pressure.intPart,
					message.pressure.decPart);


			for ( i = 0; i < UIP_DS6_ADDR_NB; i += 1) {
				if ( uip_ds6_if.addr_list[i].isused) {
					message.original_ip_address = uip_ds6_if.addr_list[i].ipaddr;
					printf("Original ip Address: "); uip_debug_ipaddr_print(&message.original_ip_address); printf("\n");
				}
			}
#endif

			if (addr != NULL){
				clock_wait(random_rand()%(1000));
				simple_udp_sendto(&unicast_connection, &message, sizeof(message), addr);

			}
			else printf("Indirizzo non valido\n");
			printf("---------------------------------------\n\n");

			break;
		}
		printf("-----------------------------------------------------------------------------\n\n");

	}

	PROCESS_END();
}


/*---------------------------------------------------------------------------*/
