//
// Safety feature, in case programming goes bananas
// Stop keyboard while pressing an arrow button while plugging keyboard in
//
bool keyboardActive = false;

//
// Pin assignment
//
const int pot_sensorPins[] = {A3, A2, A0, A1};
const int readPins[] = {15,14,16,10};          // reading pins for each block
const int writePins[] = {3, 5, 2, 4, 6, 7};    // pins to set the key block
const int LEDPins[] = {8, 9};                  // LED pins for indicators
long LED_Blinker_Time = 0;
bool LED_Blinker = HIGH;

//
// arrays are used to map values for each of four potentiometers
//
int pot_Low[]= {0, 0, 0, 0};
int pot_Middle[]= {512, 512, 512, 512};  
int pot_High[]= {1023, 1023, 1023, 1023};  
int pot_Calibrated_Low[]= {50, -50, 20, 20};  
int pot_Calibrated_High[]= {-50, 50, -20, -20};  
signed char pot_Position[4];
int mouse_Counter = 0;

//
// arrays are used to map values for each 21 buttons and 2 pedals
//
int left[]    = {0, 0, 0, 0};                  // the last reading from each finger group [current code, last code, buttons pressed, max pressed]
int right[]   = {0, 0, 0, 0};
bool bottom[] = {false,false,false,false,false,false,false,false};
bool repeatKeyMode = false; 
int shiftMode = 0;                             // Control keys
bool shift_Pressed = false;
long shift_Pressed_Time = 0;
bool alt_Pressed = false;
bool control_Pressed = false;
int funMode = 0;
bool fun_Pressed = false;
long fun_Pressed_Time = 0;
bool space_L_Pressed = false;
bool space_R_Pressed = false;
bool space_L_Consumed = false;
bool space_R_Consumed = false;
bool pedal_L_Pressed = false;
bool pedal_R_Pressed = false;
bool win_Requested = false;
int specialMode = 0;
bool special_Requested  = false;
bool button_L = false;
bool button_R = false;
bool button_M = false;

//
// Arrays to control arrow buttons
//
char arrow_buttons[] = {_CH0, _CH0, _CH0, _CH0};
const char arrowMap_0[] = {_LEFT,_UP,_DOWN,_RIGHT};
const char arrowMap_1[] = {_HOM,_PUP,_PDN,_END};

//
// Button assignments
//
const char comKeys[] = {_HOM,_END,_PUP,_PDN,_INS,_RTN,_PRN};
const char ctrlKeys0[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
const char ctrlKeys1[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

const char leftMapping[] =  {_CH0, 'e', 'a', 't', 'l', 'p', 's', 'c',_DEL, 'w', 'C','X',_TAB,_ESC, 'C', 'X',
                             _CH0, 'g', 'r', 'x', 'u', 'b', 'z', 'y', '-',_CH0,_CH0, '_',_CH0,_CH0,_HOM,_CH0,
                             _CH0, '1', '2', '3', '4', '5', '6', '7', '8', '9',_CH0,_CH0, '9', '.', '0', '9',
                             _CH0, '6', '7', '8', '9', '-', '0', '0', 'e',_CH0,_CH0,_CH0,_CH0,_CH0,_CH0,_CH0,
                             _CH0,_F05,_F04,_F06,_F03, 'L',_F02,_PRN,_INS,_CH0,_CH0,_CH0,_F01,_CH0,_CPS,_CPS,
                             _CH0,_CH0,_CH0,_CH0,_CH0,_CH0,_CH0,_CH0,_CH0,_CH0,_CH0,_CH0,_CH0,_CH0,_CH0,_CH0};
const char rightMapping[] = {_CH0, 'i', 'o', 'n', 'r', 'y', 'h', 'k',_BSP, 'q', 'V', 'Z',_RTN,_CH0, 'V', 'Z',
                              ' ', '[', ']', '<', '%', '^', '>', 'z', ';', 'x',_CH0,_CH0, ';',_CH0,_END,_CPS,
                             _CH0, ',', '.', '!', '?',_CH0, ':',_CH0, ';',_CH0,_CH0,_CH0, ';',_CH0,_CH0,_CH0,
                             _CH0, ';', ';',_CH0,_CH0,_CH0,_CH0,_CH0,_CH0,_CH0,_CH0,_CH0,_CH0,_CH0,_CH0,_CH0,
                             _CH0,_F07,_F08,_F10,_F09, 'R',_F11,_F12,_CH0,_CH0,_CH0,_CH0,_F11,_CH0,_F05,_F06,
                             _CH0,_CH0,_CH0,_CH0,_CH0,_CH0,_CH0,_CH0,_CH0,_CH0,_CH0,_CH0,_CH0,_CH0,_CH0,_CH0};

// add 136 to the scan code
const char keypad_buttons[] = {(char)'\352',(char)'\341',(char)'\342',(char)'\343',(char)'\344',(char)'\345',(char)'\346',(char)'\347',(char)'\350',(char)'\351'};
