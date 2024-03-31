/*! \file tesla.h
  \brief OOK Application for TESLA Charging port Opener
*/

//! Enter the TESLA application.
void tesla_init();

//! Exit the TESLA application.
int tesla_exit();

//! Draw the TESLA screen.
void tesla_draw();

//! Handle an incoming packet.
void tesla_packetrx(uint8_t *packet, int len);

//! Callback after transmission.
void tesla_packettx();

//! Keypress handler for the TESLA applet.
int tesla_keypress(char ch);

