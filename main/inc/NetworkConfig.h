/*
 * NetworkConfig.h
 *
 * Defines the configuration for the wlan-network
 */

#ifndef NETWORKCONFIG_H_
#define NETWORKCONFIG_H_


// Define ONE connection type:
// ---------------------------
//#define	InfraJoin		// join infrastructure network without password
//#define	InfraPwJoin		// join infrastructure network with password
//#define	AdhocJoin		// join ad-hoc network without password
//#define	AdhocPwJoin		// join ad-hoc network with password
#define	AdhocCreate		// create ad-hoc network without password
//#define	AdhocPwCreate	// create ad-hoc network with password

// network settings:
// -----------------
#if defined(AdhocJoin) || defined(AdhocPwJoin) || defined(AdhocCreate) || defined(AdhocPwCreate)
	char *ssid = "AdhocNetworkArduino";
	char *pw   = "arduinoflynet";
	uint8_t channel = 11;
#elif defined(InfraJoin) || defined(InfraPwJoin)
	char *ssid = "***-*****";				// enter your ssid here
	char *pw   = "****-****-****-****";  	// enter your password here
#endif

byte ip[]      = { 192,168,  1, 30 };
byte netmask[] = { 255,255,255,  0 };

// Port definitions:
// -----------------
#define TCP_PORT  (80)   //local TCP port on the shield
#define UDP_PORT  (9048) //local UDP port on the shield

// socket handles:
// ---------------
uint8_t hTCP=0xFF;
uint8_t hUDP=0xFF;

// definitions for the terminal application:
// -----------------------------------------
byte destIP[4];
uint16_t destPORT = 0;

#endif /* NETWORKCONFIG_H_ */
