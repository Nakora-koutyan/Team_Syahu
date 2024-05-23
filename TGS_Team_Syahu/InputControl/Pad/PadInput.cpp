#include "PadInput.h"

char PadInput::nowKey[BUTTON];
char PadInput::oldKey[BUTTON];
XINPUT_STATE PadInput::input;
Stick PadInput::l_stick;
Stick PadInput::r_stick;