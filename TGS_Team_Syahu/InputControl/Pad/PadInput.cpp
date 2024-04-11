#include "PadInput.h"

char PadInput::now_key[BUTTON];
char PadInput::old_key[BUTTON];
XINPUT_STATE PadInput::input;
Stick PadInput::l_stick;
Stick PadInput::r_stick;