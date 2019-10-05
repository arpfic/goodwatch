/* 
 * File:   jukebox.h
 * Author: NotPike
 */

//! Enter the OOK application.
void jukebox_init();

//! Exit the OOK application.
int jukebox_exit();

//! Draw the OOK screen.
void jukebox_draw();

//! Handle an incoming packet.
void jukebox_packetrx(uint8_t *packet, int len);

//! Callback after transmission.
void jukebox_packettx();

//! Keypress handler for the OOK applet.
int jukebox_keypress(char ch);

//! NEC Encoder
char encode(uint8_t *out, uint8_t command, int pin);

// Packet Building Helper Function
uint8_t* build_jukebox_packet(int cmd, int pin);

void pinInput(char ch);


/*
*────────────────────────────────┌ ─────────────────────────────────╒░░░░░░░░░░░░
*───────────────────────────── ┌  ┐ ────────────────────────────────╒░░░┘    └░░░
*─────────────────────────░─┌   ╒─ ─────────────────────────────────╒░░  ┌──   ░░
*──────   ──   ────────── ┌    ╒┬┼─╘ ───────────────────────────────╒░░  ░░░┴  ░░
*──────╘          ─╓╖╤░░░░░░══┬╔╓╒┴─╕───────────────────────────────╒░░   ░░   ░░
*       ╓  ┐───     ░░░░░░░░░░░░░╙╚╖▐                               └░░═─┌░░─╔░░░
*       ╒╕  ─  └  ┌░░░░░░░░░░░░░░░░░╙╖                               ░░─    └═░░░
*       └╙░ └╗  ┌┬░░╔░░░░░░░░░░░░░░░░░╗                              ░░░┐ ═╦─  ░░
*          ▄▓  ─╜░░░░░░░╙░░░░░░░░░░░╔╔╔╗╔╠                           ░░░─     ┌░░
*          └╘┬┌░░░░░░░░░░╠╠╩╝░░░░░╚░░░░░╩                            ░░  ┌═░░░░░░
*───────────▐░░░░░░░░░░╚╠░░░╤╗╦╥░░░╥╥╤╚╜░╔╦╩ ───────────────────────░░░┘ ┌┘   └░░
*           ▐╜░╤╙╙░░░░╦╩ └╙╦╔░░░░░░░░░╥╦╩╨                          ─░░  ░  ░  ░░
*─────────── ╫╫╦╦╦╗╦╩╩░╪╘╙▀▌╙ ┴└└╙╙╙└┴╦╦ ───────────────────────────╔░░  ═  ═  ░░
*             ╙╫╩╩▒╪░░░▐═╨         ╙  ╞╩░                           └░░═   ╔┐┌═░░
*────────────╓╦╠╩╩╫╪░░░╙              ╫╩░───────────────────────────╔░░─       ░░
*───────────└╨╩╠╩╩╠╬░░░░╦           ╥╫╩╩═───────────────────────────╒░░═╦════╦═░░
*────────────── ▐╩╩╠╚╦░░╠╔─▐▀▀▓▌ ─ ╩╫╚╩╩ ───────────────░──░─╓▄─────╒░░┘      └░░
*──────────────╓╠╫╩   └═╚   ▄──┴──┴┴╠═╨ ───────────── ╙▐  ┌  ╒└ ─╓╓─░░░  ░░░░  ░░
*────────────────└═──       ▐   ───╔░╕──────────────╒╞─   ─└    ┌▀╙─░░░  ═░░░  ░░
*──────────────┌         ┌─└─┐    ░┼░╟┐────────── ┌┘        ── ┌─░──╒░░═      ╔░░
*──────────── ┘                 └══░╔╓▐╕ ░─────╓┐             └ ────╒░░░░░░░░░░░░
*──────────── ╕┐         ┌ ╕         └╘╜┼╔┐ ─┌╠▓▓▓▄┐         ┐ ─────╒░░░░░░░░░░░░
*─────────────└╡ ╒ ─        ╙             ╙└╠▓▀▓▓▀║▓▒ ───└┌┌└───────╒░░░░░░░░░░░░
*──────────────╞┌    ╓▄─═╙┴──░             ╒╠║▓▒╢▀▌╠┘─░─────────────╒░░░░░░░░░░░░
*──────────────╓  ╓▄▓▀▄▓     ╘            ╧░│╫╦▀▒▄    ┐ ░───────────╒░░░░░░░░░░░░
*───────────────│└╦╙═▄╝▌      ╔         ╥░░░░░╚╦╨╤      ═ ░─────────╒░░░░░░░░░░░░
*─────░─  ───────░ ╤ ╢▓╓╕      ┐      ┘ ╔░░░░░╔           ┐─────────╒░░░░░░░░░░░░
*─── ─  ╛ ────────░ ▐─          ┐  ─      └─ ╒       ┐     ┐────────╒░░░░░░░░░░░░
*─┌─   ┌ ────────────╙╤          ┌          ╒                ───────╒░░░░░░░░░░░░
*╔└     ░────────────░ ╚─                  ╒         ┌     ╒ ───────╒░░░░░░░░░░░░
*─      ────────────────╘╦                ╔                ╛────────╒░░░░░░░░░░░░
*─      ────────────────┌ ╦┌             ╝─        ─┴─   ╒└─────────╒░░░░░░░░░░░░
*─     ┌──────────────────▐┬╖─         ╤┴     ──░─╒┴──┬═╙─░─────────╒░░░░░░░░░░░░
*─       ──────────────── ╨┐╨┴╓─    ╒┴┴───────┐┬╓░░═╙└──────────────╒░░░░░░░░░░░░
*─░      ─ ──────────── ╓╦╓┬─└┌─┴══┴─  ──      └    ────────────────╒░░░░░░░░░░░░
*░──        ──────────╓╫╫╩╫╬╦╦╩╗┴─          ╥ ╓╤╩╡ ─────────────────╒░░░░░░░░░░░░
*─└┬──       ─ ────╓╦╬╩╩╩╩╩╩╫░░░╙░╩╥╥╓╓╓╓╤╩┼░░░░─▐ ─────────────────╒░░░░░░░░░░░░
* ╗─┬┬┴┌─         ╒░╨╠╩╬╩╩╩╩░░░░░░░░░░░░░░░░╔░░░─▐ ─────────────────╒░░░░░░░░░░░░
*──└└═╓──────── ┌╕───╙╬╩╠╩╬╠░░░░░░╔╥░╤╤░░╩╨╚░░░╠── ─────────────────╒░░░░░░░░░░░░
* Original Art By: @theycallhimcake
*/