#ifndef MESSAGE_H
#define MESSAGE_H

#include "net/rpl/rpl.h"

typedef enum {ROOT_GET, ROOT_GET_ALL, SET_VALUE, UPDATE } tMessage_t;

typedef struct sensor_value{
	int32_t decPart;
	int32_t intPart;
}sensor_value_t;

typedef struct our_message {
	int message_id;
	tMessage_t message_type;
	sensor_value_t temperature;
	sensor_value_t humidity;
	sensor_value_t pressure;
	uip_ipaddr_t original_ip_address;
	uip_ipaddr_t final_ip_destination;
	char name [10];
} our_message_t;


typedef struct message_list {
	uip_ipaddr_t addr;
	int message_id;
	sensor_value_t temperature;
	sensor_value_t humidity;
	sensor_value_t pressure;
	tMessage_t message_type;
	char name[20];
} message_list_t;

#endif
