#include "le3dp_rptparser.h"

JoystickReportParser::JoystickReportParser(JoystickEvents *evt) :
	joyEvents(evt)
{}

void JoystickReportParser::Parse(HID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf)
{
	bool match = true;

	// Checking if there are changes in report since the method was last called
	for (uint8_t i=0; i<RPT_GAMEPAD_LEN; i++) {
		if( buf[i] != oldPad[i] ) {
			match = false;
			break;
		}
  }
  	// Calling Game Pad event handler
	if (!match && joyEvents) {
		joyEvents->OnGamePadChanged((const GamePadEventData*)buf);

		for (uint8_t i=0; i<RPT_GAMEPAD_LEN; i++) oldPad[i] = buf[i];
	}
}

void JoystickEvents::OnGamePadChanged(const GamePadEventData *evt)
{
	Serial.print("x");
	Serial.print(evt->x);
	Serial.print("y");
	Serial.print(evt->y);
	Serial.print("h");
	Serial.print(evt->hat);
	Serial.print("t");
	Serial.print(evt->twist);
	Serial.print("s");
	Serial.print(evt->slider);
  Serial.print("a");
	Serial.print(evt->buttons_a);
	Serial.print("b");
	Serial.print(evt->buttons_b);
	Serial.println("");
}
