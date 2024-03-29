/* Copyright (C) 2011 TKJ Electronics. All rights reserved.
 
 This software may be distributed and modified under the terms of the GNU
 General Public License version 2 (GPL2) as published by the Free Software
 Foundation and appearing in the file GPL2.TXT included in the packaging of
 this file. Please note that GPL2 Section 2[b] requires that all works based
 on this software must also be made publicly available under the terms of
 the GPL2 ("Copyleft").
 
 Contact information
 -------------------
 
 TKJ Electronics
 Web      :  http://www.tkjelectronics.com
 e-mail   :  mail@tkjelectronics.com
 */

#ifndef _ps3bt_h_
#define _ps3bt_h_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Usb.h"

/*The application will work in reduced host mode, so we can save program and data
 memory space. After verifying the PID and VID we will use known values for the 
 configuration values for device, interface, endpoints and HID */

/* CSR Bluetooth data taken from descriptors */
#define INT_MAXPKTSIZE   	16 // max size for HCI data
#define BULK_MAXPKTSIZE  	64 // max size for ACL data

/* PS3 data taken from descriptors */
#define EP_MAXPKTSIZE   	64 // max size for data via USB

/* Endpoint types */
#define EP_INTERRUPT 		0x03
#define EP_BULK 			0x02

#define CSR_CONTROL_PIPE 	0 // names we give to the 4 pipes
#define CSR_EVENT_PIPE 		1
#define CSR_DATAIN_PIPE 	2
#define CSR_DATAOUT_PIPE 	3

#define PS3_CONTROL_PIPE 	0 // names we give to the 3 pipes
#define PS3_OUTPUT_PIPE 	1
#define PS3_INPUT_PIPE 		2

//PID and VID of the different devices
#define CSR_VID 			0x0A12  // Cambridge Silicon Radio Ltd.
#define CSR_PID 			0x0001  // Bluetooth HCI Device
#define PS3_VID 			0x054C  // Sony Corporation
#define PS3_PID 			0x0268  // PS3 Controller DualShock 3
#define PS3NAVIGATION_VID 	0x054C  // Sony Corporation
#define PS3NAVIGATION_PID 	0x042F  // Navigation controller
#define PS3MOVE_VID 		0x054C  // Sony Corporation
#define PS3MOVE_PID 		0x03D5  // Motion controller

#define HIDMOVEBUFFERSIZE 			50 // size of the buffer for the Playstation Motion Controller
#define OUTPUT_REPORT_BUFFER_SIZE 	48 // size of the output report buffer for the controllers

// used in control endpoint header for HCI Commands
#define bmREQ_HCI_OUT USB_SETUP_HOST_TO_DEVICE|USB_SETUP_TYPE_CLASS|USB_SETUP_RECIPIENT_DEVICE

// used in control endpoint header for HID Commands
#define bmREQ_HIDOUT USB_SETUP_HOST_TO_DEVICE|USB_SETUP_TYPE_CLASS|USB_SETUP_RECIPIENT_INTERFACE
#define HID_REQUEST_SET_REPORT 0x09

/* Bluetooth HCI states for hci_task() */
#define HCI_INIT_STATE 			0
#define HCI_RESET_STATE 		1
#define HCI_BDADDR_STATE 		2
#define HCI_SCANNING_STATE 		3
#define HCI_CONNECT_IN_STATE 	4
#define HCI_REMOTE_NAME_STATE	5
#define HCI_CONNECTED_STATE 	6
#define HCI_DISABLE_SCAN 		7
#define HCI_DONE_STATE 			8
#define HCI_DISCONNECT_STATE 	9

/* HCI event flags*/
#define HCI_FLAG_CMD_COMPLETE 			0x01
#define HCI_FLAG_CMD_STATUS 			0x02
#define HCI_FLAG_CONN_COMPLETE 			0x04
#define HCI_FLAG_DISCONN_COMPLETE 		0x08
#define HCI_FLAG_CONNECT_OK 			0x10
#define HCI_FLAG_REMOTE_NAME_COMPLETE 	0x20
#define HCI_FLAG_INCOMING_REQUEST 		0x40

/*Macros for HCI event flag tests */
#define hci_cmd_complete 				(hci_event_flag & HCI_FLAG_CMD_COMPLETE)
#define hci_cmd_status 					(hci_event_flag & HCI_FLAG_CMD_STATUS)
#define hci_connect_complete 			(hci_event_flag & HCI_FLAG_CONN_COMPLETE)
#define hci_disconnect_complete 		(hci_event_flag & HCI_FLAG_DISCONN_COMPLETE)
#define hci_connect_ok 					(hci_event_flag & HCI_FLAG_CONNECT_OK)
#define hci_remote_name_complete 		(hci_event_flag & HCI_FLAG_REMOTE_NAME_COMPLETE)
#define hci_incoming_connect_request	(hci_event_flag & HCI_FLAG_INCOMING_REQUEST)

/* HCI Events managed */
#define EV_COMMAND_COMPLETE  			0x0E
#define EV_COMMAND_STATUS    			0x0F
#define EV_CONNECT_COMPLETE  			0x03
#define EV_DISCONNECT_COMPLETE 			0x05
#define EV_NUM_COMPLETE_PKT  			0x13
#define EV_INQUIRY_COMPLETE  			0x01
#define EV_INQUIRY_RESULT    			0x02
#define EV_REMOTE_NAME_COMPLETE			0x07
#define EV_INCOMING_CONNECT  			0x04
#define EV_ROLE_CHANGED  				0x12

/* Bluetooth L2CAP states for L2CAP_task() */
#define L2CAP_EV_WAIT 					0
#define L2CAP_EV_CONTROL_SETUP 			1
#define L2CAP_EV_CONTROL_REQUEST 		2
#define L2CAP_EV_CONTROL_SUCCESS 		3
#define L2CAP_EV_INTERRUPT_SETUP 		4
#define L2CAP_EV_INTERRUPT_REQUEST 		5
#define L2CAP_EV_INTERRUPT_SUCCESS 		6
#define L2CAP_EV_HID_ENABLE_SIXAXIS 	7
#define L2CAP_EV_L2CAP_DONE 			8
#define L2CAP_EV_INTERRUPT_DISCONNECT 	9
#define L2CAP_EV_CONTROL_DISCONNECT 	10

/* L2CAP event flags */
#define L2CAP_EV_CONTROL_CONNECTION_REQUEST 	0x01
#define L2CAP_EV_CONTROL_CONFIG_REQUEST 		0x02
#define L2CAP_EV_CONTROL_CONFIG_SUCCESS 		0x04
#define L2CAP_EV_INTERRUPT_CONNECTION_REQUEST 	0x08
#define L2CAP_EV_INTERRUPT_CONFIG_REQUEST 		0x10
#define L2CAP_EV_INTERRUPT_CONFIG_SUCCESS 		0x20
#define L2CAP_EV_CONTROL_DISCONNECT_RESPONSE 	0x40
#define L2CAP_EV_INTERRUPT_DISCONNECT_RESPONSE	0x80

/*Macros for L2CAP event flag tests */
#define l2cap_control_connection_request 	(l2cap_event_flag & L2CAP_EV_CONTROL_CONNECTION_REQUEST)
#define l2cap_control_config_request 		(l2cap_event_flag & L2CAP_EV_CONTROL_CONFIG_REQUEST)
#define l2cap_control_config_success 		(l2cap_event_flag & L2CAP_EV_CONTROL_CONFIG_SUCCESS)
#define l2cap_interrupt_connection_request 	(l2cap_event_flag & L2CAP_EV_INTERRUPT_CONNECTION_REQUEST)
#define l2cap_interrupt_config_request 		(l2cap_event_flag & L2CAP_EV_INTERRUPT_CONFIG_REQUEST)
#define l2cap_interrupt_config_success 		(l2cap_event_flag & L2CAP_EV_INTERRUPT_CONFIG_SUCCESS)
#define l2cap_control_disconnect_response 	(l2cap_event_flag & L2CAP_EV_CONTROL_DISCONNECT_RESPONSE)
#define l2cap_interrupt_disconnect_response	(l2cap_event_flag & L2CAP_EV_INTERRUPT_DISCONNECT_RESPONSE)

/* L2CAP signaling commands */
#define L2CAP_CMD_COMMAND_REJECT 		0x01
#define L2CAP_CMD_CONNECTION_REQUEST 	0x02
#define L2CAP_CMD_CONNECTION_RESPONSE 	0x03
#define L2CAP_CMD_CONFIG_REQUEST 		0x04
#define L2CAP_CMD_CONFIG_RESPONSE 		0x05
#define L2CAP_CMD_DISCONNECT_REQUEST 	0x06
#define L2CAP_CMD_DISCONNECT_RESPONSE	0x07

/* Bluetooth L2CAP PSM */
#define L2CAP_PSM_HID_CTRL 0x11 // HID_Control        
#define L2CAP_PSM_HID_INTR 0x13 // HID_Interrupt

// Used For Connection Response - Remember to Include High Byte
#define PENDING 	0x01
#define SUCCESSFUL	0x00

#define bConfigurationValue 0x01 // Used to set configuration

#define PS3_MAX_ENDPOINTS 4

enum LED
{
    LED1  = 0x01,
    LED2  = 0x02,
    LED3  = 0x04,
    LED4  = 0x08,
    
    LED5  = 0x09,
    LED6  = 0x0A,
    LED7  = 0x0C,
    LED8  = 0x0D,
    LED9  = 0x0E,
    LED10 = 0x0F,
};
enum Colors
{
    //Used to set the colors of the move controller            
    Red       = 0xFF0000,	// ((255 << 16) | (  0 << 8) | 0);
    Green     = 0xFF00,		// ((  0 << 16) | (255 << 8) | 0);
    Blue      = 0xFF,		// ((  0 << 16) | (  0 << 8) | 255);
    
    Yellow    = 0xFFEB04,	// ((255 << 16) | (235 << 8) | 4);
    Lightblue = 0xFFFF,		// ((  0 << 16) | (255 << 8) | 255);
    Purble    = 0xFF00FF,	// ((255 << 16) | (  0 << 8) | 255);
    
    White     = 0xFFFFFF,	// ((255 << 16) | (255 << 8) | 255);
    Off       = 0x00,		// ((  0 << 16) | (  0 << 8) | 0);
};

enum Button
{
    // byte location | bit location
    
    //Sixaxis Dualshcock 3 & Navigation controller 
    SELECT   = (11 << 8) | 0x01,
    L3       = (11 << 8) | 0x02,
    R3       = (11 << 8) | 0x04,
    START    = (11 << 8) | 0x08,
    UP       = (11 << 8) | 0x10,
    RIGHT    = (11 << 8) | 0x20,
    DOWN     = (11 << 8) | 0x40,
    LEFT     = (11 << 8) | 0x80,
    
    L2       = (12 << 8) | 0x01,
    R2       = (12 << 8) | 0x02,
    L1       = (12 << 8) | 0x04,
    R1       = (12 << 8) | 0x08,
    TRIANGLE = (12 << 8) | 0x10,
    CIRCLE   = (12 << 8) | 0x20,
    CROSS    = (12 << 8) | 0x40,
    SQUARE   = (12 << 8) | 0x80,
    
    PS       = (13 << 8) | 0x01,
    
    //Playstation Move Controller
    SELECT_MOVE   = (10 << 8) | 0x01,
    START_MOVE    = (10 << 8) | 0x08,
    
    TRIANGLE_MOVE = (11 << 8) | 0x10,
    CIRCLE_MOVE   = (11 << 8) | 0x20,
    CROSS_MOVE    = (11 << 8) | 0x40,
    SQUARE_MOVE   = (11 << 8) | 0x80,
    
    PS_MOVE       = (12 << 8) | 0x01,
    MOVE_MOVE     = (12 << 8) | 0x08,	//covers 12 bits - we only need to read the top 8
    T_MOVE        = (12 << 8) | 0x10,	//covers 12 bits - we only need to read the top 8
};
enum AnalogButton
{
    //Sixaxis Dualshcock 3 & Navigation controller
    UP_ANALOG       = 23,
    RIGHT_ANALOG    = 24,
    DOWN_ANALOG     = 25,
    LEFT_ANALOG     = 26,
    
    L2_ANALOG       = 27,
    R2_ANALOG       = 28,
    L1_ANALOG       = 29,
    R1_ANALOG       = 30,
    TRIANGLE_ANALOG = 31,
    CIRCLE_ANALOG   = 32,
    CROSS_ANALOG    = 33,
    SQUARE_ANALOG   = 34,
    
    //Playstation Move Controller
    T_MOVE_ANALOG   = 15,	// Both at byte 14 (last reading) and byte 15 (current reading)
};
enum AnalogHat
{
    LeftHatX  = 15,
    LeftHatY  = 16,
    RightHatX = 17,
    RightHatY = 18,
};
enum Sensor
{
    //Sensors inside the Sixaxis Dualshock 3 controller
    aX = 50,
    aY = 52,
    aZ = 54,
    gZ = 56,
    
    //Sensors inside the move motion controller - it only reads the 2nd frame
    aXmove = 28,
    aZmove = 30,
    aYmove = 32,
    
    gXmove = 40,
    gZmove = 42,
    gYmove = 44,
    
    tempMove = 46,
    
    mXmove = 47,
    mZmove = 49,
    mYmove = 50,            
};
enum Angle
{
    Pitch = 0x01,
    Roll = 0x02,
};
enum Status
{
    // byte location | bit location
    Plugged         = (38 << 8) | 0x02,
    Unplugged       = (38 << 8) | 0x03,
    
    Charging        = (39 << 8) | 0xEE,
    NotCharging     = (39 << 8) | 0xF1,
    Shutdown        = (39 << 8) | 0x01,
    Dying           = (39 << 8) | 0x02,
    Low             = (39 << 8) | 0x03,
    High            = (39 << 8) | 0x04,
    Full            = (39 << 8) | 0x05,
    
    MoveCharging    = (21 << 8) | 0xEE,
    MoveNotCharging = (21 << 8) | 0xF1,
    MoveShutdown    = (21 << 8) | 0x01,
    MoveDying       = (21 << 8) | 0x02,
    MoveLow         = (21 << 8) | 0x03,
    MoveHigh        = (21 << 8) | 0x04,
    MoveFull        = (21 << 8) | 0x05,
    
    CableRumble     = (40 << 8) | 0x10,	// Opperating by USB and rumble is turned on
    Cable           = (40 << 8) | 0x12,	// Opperating by USB and rumble is turned off
    BluetoothRumble = (40 << 8) | 0x14,	// Opperating by bluetooth and rumble is turned on
    Bluetooth       = (40 << 8) | 0x16,	// Opperating by bluetooth and rumble is turned off
};
enum Rumble
{
    RumbleHigh = 0x10,
    RumbleLow = 0x20,            
};

class PS3BT : public USBDeviceConfig
{
public:            
    PS3BT(USB *pUsb);
    
    // USBDeviceConfig implementation
    virtual uint8_t Init(uint8_t parent, uint8_t port, bool lowspeed);
    virtual uint8_t Release();
    virtual uint8_t Poll();
    virtual uint8_t GetAddress() { return bAddress; };
        
    void setBdaddr(uint8_t* BDADDR);
    void setMoveBdaddr(uint8_t* BDADDR);
    
    /* PS3 Controller Commands */
    bool getButton(Button b);
    uint8_t getAnalogButton(AnalogButton a);
    uint8_t getAnalogHat(AnalogHat a);
    uint32_t getSensor(Sensor a);
    double getAngle(Angle a, boolean resolution);
    bool getStatus(Status c);  
    String getStatusString();    
    void disconnect(); // use this void to disconnect any of the controllers
    
    /* HID Commands */

    /* Commands for Dualshock 3 and Navigation controller */    
    void setAllOff();
    void setRumbleOff();
    void setRumbleOn(Rumble mode);
    void setLedOff(LED a);
    void setLedOn(LED a);

    /* Commands for Motion controller only */    
    void moveSetBulb(uint8_t r, uint8_t g, uint8_t b);	// Use this to set the Color using RGB values
    void moveSetBulb(Colors color);						// Use this to set the Color using the predefined colors in "enum Colors"
    void moveSetRumble(uint8_t rumble);
    
    bool PS3BTConnected;			// Variable used to indicate if the normal playstation controller is successfully connected
    bool PS3MoveBTConnected;		// Variable used to indicate if the move controller is successfully connected
    bool PS3NavigationBTConnected;	// Variable used to indicate if the navigation controller is successfully connected
    bool ButtonChanged;				// Indicate if a button has been changed
    bool ButtonPressed;				// Indicate if a button has been pressed
    
protected:           
    /* mandatory members */
    USB *pUsb;
    uint8_t	bAddress;	
    EpInfo epInfo[PS3_MAX_ENDPOINTS]; //endpoint info structure
    
private:        
    bool bPollEnable;
    int8_t frep_debug_1;	// frepfrep
    
    /*variables filled from HCI event management */
    int16_t  hci_handle;
    uint8_t  disc_bdaddr[6]; 		// maximum of three discovered devices
    uint8_t  remote_name[30]; 		// first 30 chars of remote name
    //uint8_t dev_role;
    
    /* variables used by high level HCI task */    
    uint8_t  hci_state;  			//current state of bluetooth hci connection
    uint16_t hci_counter; 			// counter used for bluetooth hci reset loops
    uint16_t hci_event_flag;		// hci flags of received bluetooth events
    
    /* variables used by high level L2CAP task */    
    uint8_t  l2cap_state;
    uint16_t l2cap_event_flag;		// l2cap flags of received bluetooth events
    
    uint32_t ButtonState;
    uint32_t OldButtonState;
    uint32_t timerHID;				// timer used see if there has to be a delay before a new HID command
    uint32_t dtimeHID;				// delta time since last HID command
    uint32_t timerBulbRumble;		// used to continuously set PS3 Move controller Bulb and rumble values
    uint32_t dtimeBulbRumble;		// used to know how longs since last since the Bulb and rumble values was written
    
    uint8_t my_bdaddr[6]; 						//Change to your dongles Bluetooth address in PS3BT.cpp
    uint8_t ps3Ctrl_bdaddr[6];					// frepfrep: store bdaddr of the ps3 controller
    uint8_t hcibuf[BULK_MAXPKTSIZE];			//General purpose buffer for hci data
    uint8_t l2capinbuf[BULK_MAXPKTSIZE];		//General purpose buffer for l2cap in data
    uint8_t l2capoutbuf[BULK_MAXPKTSIZE];		//General purpose buffer for l2cap out data
    uint8_t HIDBuffer[BULK_MAXPKTSIZE];			// Used to store HID commands
    uint8_t HIDMoveBuffer[HIDMOVEBUFFERSIZE];	// Used to store HID commands for the Move controller
    
    /* L2CAP Channels */
    uint8_t control_scid[2];	// L2CAP source CID for HID_Control
    uint8_t control_dcid[2];	//0x0040
    uint8_t interrupt_scid[2];	// L2CAP source CID for HID_Interrupt
    uint8_t interrupt_dcid[2];	//0x0041
    uint8_t identifier;			//Identifier for connection
    
    void HCI_event_task(); 		//poll the HCI event pipe
    void HCI_task(); 			// HCI state machine
    void ACL_event_task(); 		// start polling the ACL input pipe too, though discard data until connected
    void L2CAP_task(); 			// L2CAP state machine
    
    void readReport(); 			// read incoming data
    void printReport(); 		// print incoming date - Uncomment for debugging
    
    /* HCI Commands */
    void HCI_Command(uint8_t* data, uint16_t nbytes);
    void hci_reset(); 
    void hci_write_scan_enable();
    void hci_write_scan_disable();
    void hci_read_bdaddr();
    void hci_accept_connection();
    void hci_remote_name();
    void hci_disconnect();
    
    /* L2CAP Commands */
    void L2CAP_Command(uint8_t* data, uint16_t nbytes);
    void l2cap_connection_response(uint8_t rxid, uint8_t dcid[], uint8_t scid[], uint8_t result);
    void l2cap_config_request(uint8_t rxid, uint8_t dcid[]);
    void l2cap_config_response(uint8_t rxid, uint8_t scid[]);
    void l2cap_disconnection_request(uint8_t rxid, uint8_t dcid[], uint8_t scid[]);
    void l2cap_disconnection_response(uint8_t rxid, uint8_t dcid[], uint8_t scid[]);    
    
    /* HID Commands */
    void HID_Command(uint8_t* data, uint16_t nbytes);
    void HIDMove_Command(uint8_t* data, uint16_t nbytes);
    void enable_sixaxis();//Command used to enable the Dualshock 3 and Navigation controller to send data via USB
};
#endif
