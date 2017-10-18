-------------------------------------------------------------------------------
-                    (C) COPYRIGHT 2017 STMicroelectronics                    -
- File:    Contiki6LP_readme.txt                                              -
- Author:  ST Central Labs                                                    -
- Date:    16-May-2017                                                        -
- Version: V1.2.0                                                             -

-----------
Contiki6LP_readme.txt
-----------
The Contiki6LP V1.2.0 is a Middleware included in the X-CUBE-SUBG1 software
expansion for STM32Cube.

Contiki is an open source operating system for the Internet of Things 
(information about the Contiki OS are available at www.contiki-os.org). 

The middleware contains the Contiki library for STM32 platform, three sample
applications are distrubuited with this software expansion as well.

For instructions on how to use the sample applications, see the files: 
 * $X-CUBE-SUBG1_INST_PATH\Projects\Multi\Applications\Contiki\Udp-receiver\readme.txt
 * $X-CUBE-SUBG1_INST_PATH\Projects\Multi\Applications\Contiki\Udp-sender\readme.txt
 * $X-CUBE-SUBG1_INST_PATH\Projects\Multi\Applications\Contiki\Border-router\readme.txt

---------
Contents
---------
In this package you can find, specifically related to Contiki6LP:
 * $X-CUBE-SUBG1_INST_PATH\Middlewares\Third_Party\Contiki\Contiki6LP_readme.txt ................ This readme.txt
   
 * Documentation:
   * $X-CUBE-SUBG1_INST_PATH\Documentation\Contiki6LP.chm ...... Documentation of the
                               Contiki6LP related source code included in this package

 * Middlewares:
   * $X-CUBE-SUBG1_INST_PATH\Middlewares\Third_Party\Contiki........................... Contiki OS v3.x (see the release note for detailed 
								                                                        information about the version)
   * $X-CUBE-SUBG1_INST_PATH\Middlewares\ST\Contiki_STM32_Library..................... ST Platform in Contiki ("target").																					
  
 * Applications:   
   * $X-CUBE-SUBG1_INST_PATH\Projects\Multi\Applications\Contiki\Udp-receiver
     * Udp-receiver ............ Sample application showing how the SPIRIT1 radio
			       can be integrated into the Contiki OS. More precisely
			       this application implements an unicast udp receiver node 
			       that receives data from a sender. The communication is
			       set up through the definition of a SERVICE_NUMBER	

   * Projects\Multi\Applications\Contiki\Udp-sender
     * Udp-sender .............. Sample application showing how the SPIRIT1 radio
			       can be integrated into the Contiki OS. More precisely
			       this application implements an unicast udp sender node 
			       that sends data to a receiver. The communication is
			       set up through the definition of a SERVICE_NUMBER
 
   * Projects\Multi\Applications\Contiki\Border-router
     * Border-router ........... Sample application showing how the SPIRIT1 radio
			       can be integrated into the Contiki OS. More precisely
			       this application configures a node as "RPL Border Router" 
			       which is the device that stands between a 6LoWPAN network 
			       and a host system (e.g. a PC) typically connected to the 
			       Wide Area Network
   
_______________________________________________________________________________
- (C) COPYRIGHT 2016 STMicroelectronics                   ****END OF FILE**** -
