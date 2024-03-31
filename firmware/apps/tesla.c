/*! \file tesla.c
  \brief Example OOK Application for TESLA Charging port Opener
*/

#include<stdio.h>
#include<string.h>
#include<msp430.h>
#include "api.h"

//Fixed packet length is easier on our packet library.
#define LEN 46

/* Settings were prototyped first in Python.  This is basic OOK with
   no preamble, no CRC, and 341µs symbol times.
 */
static const uint8_t tesla_settings[]={
  //Change these to change the rate.
  //MDMCFG4, OOKMDMCFG4,      // Modem Configuration
  //MDMCFG3, OOKMDMCFG3,      // Modem Configuration
  //These rest are consistent for all OOK emulation.
  MDMCFG2, 0x30,      // Modem Configuration, no sync
  FREND0 , 0x11,      // Front End TX Configuration
  FSCAL3 , 0xE9,      // Frequency Synthesizer Calibration
  FSCAL2 , 0x2A,      // Frequency Synthesizer Calibration
  FSCAL1 , 0x00,      // Frequency Synthesizer Calibration
  FSCAL0 , 0x1F,      // Frequency Synthesizer Calibration
  PKTCTRL0, 0x00,     // Packet automation control, fixed length without CRC.
  PKTLEN,  LEN,       // PKTLEN    Packet length.
  0,0
};

//! Array of keys for button pressing.
static const char * const button_array[] = {
  /* These were recorded with Universal Radio Hacker (URH).  You might
     need to adjust both these packets and the symbol periods defined
     above. */
  TESLACODE
};

//! Handle an incoming packet.
void tesla_packetrx(uint8_t *packet, int len){
  printf("Not yet supported.\n");
}

static char lastch=0;

//! Send a packet.
static void transmit(int index){
  //Packet begins on the third byte.
  packet_tx((uint8_t*) button_array[index]+2,
	    LEN);
}
//! Set the rate.
static void setrate(int index){
  //First two bytes are the rate.
  radio_writereg(MDMCFG4, ((uint8_t*) button_array[index])[0]);
  radio_writereg(MDMCFG3, ((uint8_t*) button_array[index])[1]);
}

//! Called after a transmission, or on a button press.
void tesla_packettx(){
  /* Schedule next packet if a number is being held.  We already set
     the bitrate in the keypress handler.
  */
  if(lastch<='1' && lastch>='0'){
    transmit(lastch-'0');
    transmit(lastch-'0');
    transmit(lastch-'0');
  }
}


//! Enter the TESLA transmitter application.
void tesla_init(){
  /* Skip this application if we haven't got a radio.
   */
  if(!has_radio){
    app_next();
  }

  lcd_string("     TESLA");

  printf("%d button entries are available.\n", sizeof(button_array)/2);
}

//! Exit the TESLA application.
int tesla_exit(){
  //Cut the radio off.
  radio_off();
  //Allow the exit.
  return 0;
}

//! Draw the TESLA screen.
void tesla_draw(){
  int state=radio_getstate();

  switch(state){
  case 0:
  case 1:
    //lcd_string("     OOK");
    break;
  case 19: //RX IDLE between transmit packets.
    lcd_string("TRANSMIT");
    break;
  case 22: //TX_OVERFLOW
    printf("TX Overflow.\n");
    radio_strobe(RF_SIDLE);
    break;
  default:
    lcd_hex(state);
    break;
  }
}

//! Keypress handler for the TESLA applet.
int tesla_keypress(char ch){
  /* When a key is first pressed, we call tesla_packettx() to kick off a
     transmission.  That function is also the callback from the packet
     library, so it will keep running in a loop until the key is
     released.
   */
  if( (lastch=ch) && ch>='0' && ch<='1' ){
    //Radio settings.
    radio_on();
    radio_writesettings(tesla_settings);
    setrate(ch-'0'); //First two bytes are the packet rate.
    radio_writepower(0x25); // 0xB0
    //Set a frequency manually rather than using the codeplug.
    radio_setfreq(433920000); // 315 in US

    //This handler will be called back as the packet finished transmission.
    tesla_packettx();
  }else{
    //Shut down the radio when the button is released.
    radio_off();
    lcd_zero(); //Clear the clock and radio indicators.
    lcd_string("   TESLA");
  }
  return 0;
}
