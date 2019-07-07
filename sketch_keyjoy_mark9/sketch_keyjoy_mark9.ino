//
// 21-button input method for stationary chorded keyboard with 2 PSP joysticks
// Left hand: 4 finger buttons and 3 mouse buttons
// Right hand: 4 finger buttons and 4 arrow buttons
// Left thumb: BACK, Shift, Control
// Right thumb: SPACE, Function, Alt
// v 6.0 04-Jul-2019
// Tested with Arduino IDE 1.8.9
// Set the board to Arduiono/Genuino Micro
// This work is public domain under GNU licence
//
#include <Keyboard.h>
#include <Mouse.h>

#define _CH0 (char)0
#define _CPS (char)0xC1
#define _F01 (char)0xC2
#define _F02 (char)0xC3
#define _F03 (char)0xC4
#define _F04 (char)0xC5
#define _F05 (char)0xC6
#define _F06 (char)0xC7
#define _F07 (char)0xC8
#define _F08 (char)0xC9
#define _F09 (char)0xCA
#define _F10 (char)0xCB
#define _F11 (char)0xCC
#define _F12 (char)0xCD
#define _PRN (char)0xCE
#define _TAB (char)0xB3
#define _RTN (char)0xB0
#define _ESC (char)0xB1
#define _INS (char)0xD1
#define _DEL (char)0xD4
#define _PUP (char)0xD3
#define _PDN (char)0xD6
#define _HOM (char)0xD2
#define _END (char)0xD5
#define _BSP (char)0xB2

#define _UP (char)0xDA
#define _DOWN (char)0xD9
#define _LEFT (char)0xD8
#define _RIGHT (char)0xD7

#define _CTRL (char)0x80
#define _SHIFT (char)0x81
#define _ALT (char)0x82
#define _GUI (char)0x83
#define _CTRL_R (char)0x84
#define _SHIFT_R (char)0x85
#define _ALT_R (char)0x86
#define _RIGHT_R (char)0x87

#define _MOUSE_DECIMATOR 5
#define _SCROLL_DELAY1 50
#define _SCROLL_DELAY4 200
#define _NULLMOUSE (signed char)0
#define _MINUSMOUSE (signed char)(-1)
#define _PLUSMOUSE (signed char)1
#define _BLINK_PERIOD 250
#define _SHIFT_RELEASE_TIME 250

// fill here your passwords
#define _PASSWORD_1 "TypeYourPasswordHere"
#define _PASSWORD_2 "TypeYourPasswordHere"
#define _PASSWORD_3 "TypeYourPasswordHere"
#define _PASSWORD_4 "TypeYourPasswordHere"
#define _PASSWORD_5 "TypeYourPasswordHere"
#define _PASSWORD_6 "TypeYourPasswordHere"
#define _PASSWORD_7 "TypeYourPasswordHere"
#define _PASSWORD_8 "TypeYourPasswordHere"
#define _PASSWORD_9 "TypeYourPasswordHere"
#define _PASSWORD_10 "TypeYourPasswordHere"
#define _PASSWORD_11 "TypeYourPasswordHere"
#define _PASSWORD_12 "TypeYourPasswordHere"
#define _PASSWORD_13 "TypeYourPasswordHere"
#define _PASSWORD_14 "TypeYourPasswordHere"
#define _PASSWORD_15 "TypeYourPasswordHere"

// Uncomment for serial debugging
//#define _DEBUG
//#define _DEBUG_MOUSE
//#define _DEBUG_KEYBOARD

// Uncomment to disable hardware while debugging
//#define _DISABLE_MOUSE
//#define _DISABLE_KEYBOARD

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

//
// Setup code here, to run once:
//
void setup()
{
  #ifdef _DEBUG
  Serial.begin(9600);
  #endif

  for ( int i = 0; i < 2; i++)
  {
    pinMode(LEDPins[i], OUTPUT);
    digitalWrite(LEDPins[i], HIGH);
  }

  Calibrate_Pots();

  for ( int i = 0; i < 4; i++)
  {
    pinMode(readPins[i], INPUT_PULLUP);
  }
  for ( int i = 0; i < 6; i++)
  {
    pinMode(writePins[i], OUTPUT);
    digitalWrite(writePins[i], HIGH);
  }

  Read_Arrow_Buttons();
  keyboardActive = (arrow_buttons[0] + arrow_buttons[1] + arrow_buttons[2] + arrow_buttons[3]) == 0;

  if ( !keyboardActive) return;
  Mouse.begin();
  Keyboard.begin();
  delay( 500);
  SetLEDs();
  return;  
}

//
// runs continuously
//
void loop()
{
  int lCombo;
  int rCombo;
  bool ProcessFurther;
  if ( keyboardActive)
  {
    Read_Bottom_Buttons();
    Read_Mouse_Buttons();
    Read_Arrow_Buttons();
    Read_Top_Buttons();
    Read_Mouse_Pots();
    if( (left[2] == 0) && (right[2] == 0) && ((left[3] > 0) || (right[3] > 0)))
    {
      #ifdef _DEBUG_KEYBOARD
      Serial.print( repeatKeyMode);
      Serial.print( "_");
      Serial.print( left[1]);
      Serial.print( "_");
      Serial.println( right[1]);
      #endif
      if( (!repeatKeyMode) && DecodeTwoHanded())
      {
        lCombo = left[1];
        if( right[1] == 16) lCombo += 32;
        if( funMode>0) lCombo += 64;
        rCombo = right[1];
        if( left[1] == 16) rCombo += 32;
        if( funMode>0) rCombo += 64;
        DecodeButtons( lCombo, leftMapping);
        DecodeButtons( rCombo, rightMapping);
      }
      for( int i=0; i<4; i++)
      {
        left[i] = 0;
        right[i] = 0;
      }
      repeatKeyMode = false;
    }
    if( ((left[1] == 16) || (left[2] >= 2)) && (right[2] == 0) && (right[3] > 0))
    {
      rCombo = right[1];
      if( left[1] == 16) rCombo += 32;
      if( DecodeTwoHanded()) DecodeButtons( rCombo, rightMapping);
      for( int i=0; i<4; i++) right[i] = 0;
      repeatKeyMode = true;
    }
    if( ((right[1] == 16) || (right[2] >= 2)) && (left[2] == 0) && (left[3] > 0))
    {
      lCombo = left[1];
      if( right[1] == 16) lCombo += 32;
      if( DecodeTwoHanded()) DecodeButtons( lCombo, leftMapping);
      for( int i=0; i<4; i++) left[i] = 0;
      repeatKeyMode = true;
    }
  }
  SetLEDs();
  #ifdef _DEBUG
  delay(500);
  #else
  // Eliminate unwanted Tx, Rx lights
  RXLED1;
  TXLED1;
  delay(5);
  #endif
  return;
}

//
// Calibrates middle points in all 4 pots, only needs to run once
//
void Calibrate_Pots()
{
  int pin, data;
  for( int i=0; i<4; i++)
  {
    pin = pot_sensorPins[i];
    data = analogRead(pin);
    for( int i=0; i<4; i++)
    {
      delay(10);
      data += analogRead(pin);
    }
    pot_Middle[i] = data/5;
    pot_Position[i] = _NULLMOUSE;
  }
  return;
}

//
// Reads the pots and sends mouse movement commands
//
void Read_Mouse_Pots()
{
  int pin, data;

  #ifndef _DEBUG
  // mouse pot reading is decimated, so the mouse is not too fast
  if( mouse_Counter != 0)
  {
    mouse_Counter++;
    if( mouse_Counter >= _MOUSE_DECIMATOR) mouse_Counter = 0;
    return;
  }
  mouse_Counter++;
  #endif

  for( int i=0; i<4; i++)
  {
    pin = pot_sensorPins[i];
    data = analogRead(pin);
    delay(3);
    data += analogRead(pin);
    data /= 2;
    NormalizeJoystickBallistic( i, data);
  }

  //
  // Normalize left joystick to -1 to 1 (scrolling speed too fast anyway)
  //
  NormalizeJoystickToOne( 2);
  NormalizeJoystickToOne( 3);

  if( fun_Pressed)
  {
    if( pot_Position[2] != 0)
    {
      if( shiftMode == 0) Keyboard_press( _SHIFT);
      Mouse_scroll( pot_Position[2], _SCROLL_DELAY1);
      if( shiftMode == 0) Keyboard_release( _SHIFT);
      funMode = 0;
    }
    if( pot_Position[3] != 0)
    {
      if( !control_Pressed) Keyboard_press( _CTRL);
      Mouse_scroll( pot_Position[3], _SCROLL_DELAY1);
      if( !control_Pressed) Keyboard_release( _CTRL);
      funMode = 0;
    }
    if( pot_Position[0] != 0 || pot_Position[1] != 0)
    {
      NormalizeJoystickToOne( 0);
      NormalizeJoystickToOne( 1);
      Mouse_move(pot_Position[0], pot_Position[1]);
      funMode = 0;
    }
  }
  else
  {
    if( pot_Position[2] != 0)
    {
      if( funMode >= 1) Mouse_scroll( pot_Position[2], _SCROLL_DELAY4);
      else Mouse_scroll( pot_Position[2], _SCROLL_DELAY1);
    }
    else
    {
      Mouse_move(pot_Position[0], pot_Position[1]);
    }
  }

  #ifdef _DEBUG_MOUSE
  Serial.print( "Mouse pointer: ");
  Serial.print( pot_Position[0])
  Serial.print(" ");
  Serial.print( pot_Position[1])
  Serial.print(" ");
  Serial.print( pot_Position[2])
  Serial.print(" ");
  Serial.println( pot_Position[3])
  #endif
  return;
}

//
// Reads 3 mouse buttons using read lines 0,1,2 and write line 3
//
void Read_Mouse_Buttons()
{
  digitalWrite( writePins[1], LOW);
  button_L = ReadPinLogical( 0);
  button_R = ReadPinLogical( 1);
  button_M = ReadPinLogical( 2);
  digitalWrite( writePins[1], HIGH);
  Mouse_set( button_L, MOUSE_LEFT);
  Mouse_set( button_R, MOUSE_RIGHT);
  Mouse_set( button_M, MOUSE_MIDDLE);
  #ifdef _DEBUG_MOUSE
  Serial.print( "Mouse buttons: ");
  Serial.print( String(button_L, DEC));
  Serial.print( String(button_M, DEC));
  Serial.println( String(button_R, DEC));
  #endif
  return;
}

//
// Reads 4 arrow buttons using read lines 0,1,2,3 and write line 1
//
void Read_Arrow_Buttons()
{
  bool button;
  digitalWrite( writePins[3], LOW);
  for( int i=0; i<4; i++)
  {
    button = ReadPinLogical( i);
    if( !button && arrow_buttons[i] != 0)
    {
      Keyboard_release( arrow_buttons[i]);
      arrow_buttons[i] = _CH0;
    }
    if( !space_L_Pressed && button && arrow_buttons[i] != arrowMap_0[i])
    {
      space_L_Consumed = false;
      if( arrow_buttons[i] != 0) Keyboard_release( arrow_buttons[i]);
      Keyboard_press( arrowMap_0[i]);
      arrow_buttons[i] = arrowMap_0[i];
    }
    if( space_L_Pressed && button && arrow_buttons[i] != arrowMap_1[i])
    {
      space_L_Consumed = true;
      if( arrow_buttons[i] != 0) Keyboard_release( arrow_buttons[i]);
      Keyboard_press( arrowMap_1[i]);
      arrow_buttons[i] = arrowMap_1[i];
    }
  }
  digitalWrite( writePins[3], HIGH);
  return;
}

//
// Reads bottom 6 buttons and pedals using control lines 4,5 and data lines 1,2,3,4
// Sends shift, alt, control, sets function and space
//
void Read_Bottom_Buttons()
{
  long t = millis();
  digitalWrite(writePins[4], LOW);
  for( int i=0; i<4; i++) bottom[i] = ReadPinLogical( i); 
  digitalWrite(writePins[4], HIGH);
  digitalWrite(writePins[5], LOW);
  for( int i=4; i<8; i++) bottom[i] = ReadPinLogical( i-4); 
  digitalWrite(writePins[5], HIGH);
  Set_Spaces();
  Set_Shift_Mode( t);
  Set_Control_Mode();
  Set_Function_Mode( t);
  Set_Alt_Mode();
  Set_Pedals();
}

//
// Sets Both Space buttons
//
void Set_Spaces()
{ 
  space_L_Pressed = bottom[0];
  space_R_Pressed = bottom[4];
}

//
// Sets Shift mode button
//
void Set_Shift_Mode(long t)
{
  if ( bottom[1] && !shift_Pressed)
  {    
    shift_Pressed = true;
    switch( shiftMode)
    {
      case 1:
        if( t-shift_Pressed_Time < _BLINK_PERIOD) shiftMode = 2;
        else shiftMode = 0;
        break;
      default:
        shiftMode++;
        if( shiftMode>2) shiftMode = 0;
        break;  
    }
    shift_Pressed_Time = t;
    if( shiftMode>0) Keyboard_press(_SHIFT);
    else Keyboard_release(_SHIFT);
    #ifdef _DEBUG_KEYBOARD
    Serial.print( "ShiftMode = ");
    Serial.println( shiftMode);
    #endif
  }
  if ( !bottom[1] && shift_Pressed)
  {
    shift_Pressed = false;
    if( shiftMode == 1 && t-shift_Pressed_Time > _SHIFT_RELEASE_TIME)
    {
      shiftMode = 0;
      Keyboard_release( _SHIFT);
    }
  }
}

//
// Sets Function mode button
//
void Set_Function_Mode(long t)
{
  if ( bottom[5] && !fun_Pressed)
  {
    fun_Pressed = true;
    switch( funMode)
    {
      case 1:
        if( t-fun_Pressed_Time < _BLINK_PERIOD) funMode = 2;
        else funMode = 0;
        break;
      default:
        funMode++;
        if( funMode>2) funMode = 0;
        break;
    }
    fun_Pressed_Time = t;
    #ifdef _DEBUG_KEYBOARD
    Serial.print( "FunMode = ");
    Serial.println( funMode);
    #endif
  }
  if ( !bottom[5] && fun_Pressed)
  {
    fun_Pressed = false;
    if( funMode == 1 && t-fun_Pressed_Time > _SHIFT_RELEASE_TIME)
    {
      funMode = 0;
    }
  }
}

//
// Sets Control mode button
//
void Set_Control_Mode()
{
  if ( bottom[2] && !control_Pressed)
  {
    control_Pressed = true;
    Keyboard_press(_CTRL_R);
    #ifdef _DEBUG_KEYBOARD
    Serial.println( "Control pressed");
    #endif
  }
  if ( !bottom[2] && control_Pressed)
  {
    control_Pressed = false;
    Keyboard_release(_CTRL_R);
    #ifdef _DEBUG_KEYBOARD
    Serial.println( "Control released");
    #endif
  }
}

//
// Sets Alt mode button
//
void Set_Alt_Mode()
{
  if ( bottom[6] && !alt_Pressed)
  {
    alt_Pressed = true;
    Keyboard_press(_ALT);
    #ifdef _DEBUG_KEYBOARD
    Serial.println( "Alt pressed");
    #endif
  }
  if ( !bottom[6] && alt_Pressed)
  {
    alt_Pressed = false;
    Keyboard_release(_ALT);
    #ifdef _DEBUG_KEYBOARD
    Serial.println( "Alt released");
    #endif
  }
}

//
// Sets Pedals
//
void Set_Pedals()
{
  if( bottom[3] && !pedal_L_Pressed)
  {
    pedal_L_Pressed = true;
  }
  if( !bottom[3] && pedal_L_Pressed)
  {
    pedal_L_Pressed = false;
    SendRusLat();
  }
  if( bottom[7] && !pedal_R_Pressed)
  {
    pedal_R_Pressed = true;
    special_Requested = !special_Requested;
  }
  if( !bottom[7] && pedal_R_Pressed)
  {
    pedal_R_Pressed = false;
  }
}

//
// Reads top 8 buttons using control lines 0 and 1 and data lines 0,1,2,3
// Adds the Space buttons using data lines 2, 3, while control sinks to 1
//
void Read_Top_Buttons()
{
    left[0] = 0;
    right[0] = 0;
    left[2] = 0;
    right[2] = 0;
    int mult = 1;
    int b;

    // Left half
    digitalWrite(writePins[0], LOW);
    for( int i=0; i<4; i++)
    {
      b = ReadPin( i);
      left[0] += mult * b;
      left[2] += b;
      mult *= 2;
    }
    digitalWrite(writePins[0], HIGH);
    if( space_L_Pressed)
    {
      left[0] += 16;
      left[2] += 1;
    }
    if ( left[2] >= left[3])
    {
      left[1] = left[0];
      left[3] = left[2];    
    }

    // Right half
    mult = 1;
    digitalWrite(writePins[2], LOW);
    for( int i=0; i<4; i++)
    {
      b = ReadPin( i);
      right[0] += mult * b;
      right[2] += b;
      mult *= 2;
    }
    digitalWrite(writePins[2], HIGH);
    if( space_R_Pressed)
    {
      right[0] += 16;
      right[2] += 1;
    }
    if ( right[2] >= right[3])
    {
      right[1] = right[0];
      right[3] = right[2];    
    }
    #ifdef _DEBUG_KEYBOARD
    if( left[0]>0 || right[0] > 0)
    {
      Serial.print( "Top buttons: ");
      Serial.print( left[0]);
      Serial.print( ", ");
      Serial.println( right[0]);
    }
    #endif
    return;
}

//
// Decodes all two-handed chords
// Returns true if further processing is requred
//
bool DecodeTwoHanded()
{
  // switch is used to speed up processing
  switch( left[1])
  {
    case 0:
      if( DecodeSpecialChord( 0, 1, "if()\n{\n}", "if :\n", "if", 2, 0)) return false;
      if( DecodeSpecialChord( 0, 4, "true", "True", "true", 0, 0)) return false;
      if( DecodeBaseChord(  0,16, ' ')) return false;
      if( DecodeStringChord( 0, 28, ";", 0, 1)) return false;
      return true;
    case 1:
      if( DecodeSpecialChord( 1, 0, "else\n{\n}", "else:\n", "else", 2, 0)) return false;
      if( DecodeSpecialChord( 1, 1, "for(int i=; i<= ; i++)\n{\n}", "for i in range( len()):\n", "for", 0, 0)) return false;
      if( DecodeSpecialChord( 1, 4, "do\n{\n}\nuntil( true)", "while True:\n\nif : break", "do", 0, 0)) return false;
      if( DecodeBaseChord( 1, 1, 'f')) return false;
      if( DecodeBaseChord( 1, 2, 'm')) return false;
      if( DecodeBaseChord( 1, 4, 'd')) return false;
      if( DecodeStringChord( 1, 5, "\"\"", 1, 0)) return false;
      if( DecodeStringChord( 1, 15, "ed", 0, 0)) return false;
      if( DecodeBaseChord( 1, 3, 'g')) return false;
      if( DecodeBaseChord( 1, 6, '-')) return false;
      if( DecodeBaseChord( 1, 7, '`')) return false;
      if( DecodeRussianChord( 1, 14, '>', '>')) return false;
      if( DecodeBaseChord( 1, 19, '7')) return false;
      return true;
    case 2:
      if( DecodeBaseChord( 2, 1, 'j')) return false;
      if( DecodeBaseChord( 2, 2, 'b')) return false;
      if( DecodeBaseChord( 2, 3, 'q')) return false;
      if( DecodeStringChord( 2, 5, "\'\'", 0, 0)) return false;
      if( DecodeBaseChord( 2, 6, '/')) return false;
      if( DecodeBaseChord( 2, 7, '\\')) return false;
      if( DecodeRussianChord( 2, 14, '<', '<')) return false;
      if( DecodeStringChord( 2, 15, "ad", 0, 0)) return false;
      if( DecodeBaseChord( 2, 19, '8')) return false;
      return true;
    case 3:
      if( DecodeSpecialChord( 3, 0, "try\n{\n}\ncatch( Exception ex)\n{\n}\nfinally\n{\n}", "try:\n\nexcept:", "try", 0, 0)) return false;
      if( DecodeSpecialChord( 3, 2, "while(true)\n{\n}", "while True:\n", "while", 0, 0)) return false;
      if( DecodeBaseChord( 3, 1, 'v')) return false;
      if( DecodeBaseChord( 3, 2, 'w')) return false;
      if( DecodeRussianChord( 3, 3, '"', '"')) return false;
      if( DecodeBaseChord( 3, 4, 'z')) return false;
      if( DecodeStringChord( 3, 6, "th", 0, 0)) return false;
      if( DecodeStringChord( 3, 14, "if ", 0, 0)) return false;
      if( DecodeStringChord( 3, 15, "un", 0, 0)) return false;
      return true;
    case 4:
      if( DecodeSpecialChord( 4, 0, "false", "False", "false", 0, 0)) return false;
      if( DecodeBaseChord( 4, 1, 'u')) return false;
      if( DecodeBaseChord( 4, 4, 'x')) return false;
      if( DecodeStringChord( 4, 5, "ly", 0, 0)) return false;
      if( DecodeBaseChord( 4, 6, '*')) return false;
      if( DecodeStringChord( 4, 14, "for", 0, 0)) return false;
      if( DecodeStringChord( 4, 15, "al", 0, 0)) return false;
      if( DecodeBaseChord( 4, 19, '9')) return false;
      return true;
    case 5:
      if( DecodeSpecialChord( 5, 0, "println();", "print( \'{:s} {:.3f}\'.format())", "print", 0, 0)) return false;
      if( DecodeBaseChord( 5, 1, '[')) return false;
      if( DecodeBaseChord( 5, 2, ']')) return false;
      if( DecodeRussianChord( 5, 4, '^', '&')) return false;
      if( DecodeStringChord( 5, 5, ";", 0, 1)) return false;
      if( DecodeStringChord( 5, 6, "ph", 0, 0)) return false;
      if( DecodePlainStringChord( 5, 14, "try:except:", 7, 1)) return false;
      return true;
    case 6:
      if( DecodeRussianChord( 6, 1, '(', '<')) return false;
      if( DecodeRussianChord( 6, 2, ')', '>')) return false;
      if( DecodeStringChord( 6, 3, "sh", 0, 0)) return false;
      if( DecodeRussianChord( 6, 6, '\'', '\'')) return false;
      if( DecodePlainStringChord( 6, 14, "for i in range( len()):", 3, 0)) return false;
      if( DecodePlainStringChord( 6, 15, "and", 0, 0)) return false;
      return true;
    case 7:
      if( DecodeBaseChord( 7, 1, '=')) return false;
      if( DecodeRussianChord( 7, 2, '@', '#')) return false;
      if( DecodeStringChord( 7, 3, "qu", 0, 0)) return false;
      if( DecodeRussianChord( 7, 4, '^', '&')) return false;
      if( DecodeStringChord( 7, 6, "ch", 0, 0)) return false;
      if( DecodeStringChord( 7, 7, "ck", 0, 0)) return false;
      if( DecodeStringChord( 7, 14, "print( )", 1, 0)) return false;
      return true;
    case 8:
      if( DecodeStringChord( 8, 15, "False", 0, 0)) return false;
      return true;
    case 11:
      if( DecodeStringChord( 11, 1, _PASSWORD_1, 0, 0)) return false;
      if( DecodeStringChord( 11, 2, _PASSWORD_2, 0, 0)) return false;
      if( DecodeStringChord( 11, 3, _PASSWORD_3, 0, 0)) return false;
      if( DecodeStringChord( 11, 4, _PASSWORD_4, 0, 0)) return false;
      if( DecodeStringChord( 11, 5, _PASSWORD_5, 0, 0)) return false;
      if( DecodeStringChord( 11, 6, _PASSWORD_6, 0, 0)) return false;
      if( DecodeStringChord( 11, 7, _PASSWORD_7, 0, 0)) return false;
      if( DecodeStringChord( 11, 8, _PASSWORD_8, 0, 0)) return false;
      if( DecodeStringChord( 11, 9, _PASSWORD_9, 0, 0)) return false;
      if( DecodeStringChord( 11, 10, _PASSWORD_10, 0, 0)) return false;
      if( DecodeStringChord( 11, 11, _PASSWORD_11, 0, 0)) return false;
      if( DecodeStringChord( 11, 12, _PASSWORD_12, 0, 0)) return false;
      if( DecodeStringChord( 11, 13, _PASSWORD_13, 0, 0)) return false;
      if( DecodeStringChord( 11, 14, _PASSWORD_14, 0, 0)) return false;
      if( DecodeStringChord( 11, 15, _PASSWORD_15, 0, 0)) return false;
      return true;
    case 12:
      if( DecodePlainStringChord( 12, 1, "+", 0, 0)) return false;
      if( DecodePlainStringChord( 12, 2, "-", 0, 0)) return false;
      if( DecodePlainStringChord( 12, 3, "&", 0, 0)) return false;
      if( DecodePlainStringChord( 12, 4, "*", 0, 0)) return false;
      if( DecodePlainStringChord( 12, 6, "|", 0, 0)) return false;
      if( DecodePlainStringChord( 12, 7, "$", 0, 0)) return false;
      if( DecodePlainStringChord( 12, 8, "/", 0, 0)) return false;
      if( DecodeBaseChord( 12, 12, _ESC)) return false;
      return true;
    case 14:
      if( DecodePlainStringChord( 14, 1, "()", 1, 0)) return false;
      if( DecodePlainStringChord( 14, 2, "[]", 1, 0)) return false;
      if( DecodePlainStringChord( 14, 3, "<>", 1, 0)) return false;
      if( DecodePlainStringChord( 14, 4, "{}", 1, 0)) return false;
      if( DecodePlainStringChord( 14, 6, "\n{}", 1, 1)) return false;
      if( DecodeStringChord( 14, 8, "ou", 0, 0)) return false;
      if( DecodeStringChord( 14, 12, ":", 0, 1)) return false;
      if( DecodeStringChord( 14, 14, "the", 0, 0)) return false;
      return true;
    case 15:
      if( DecodePlainStringChord( 15, 1, "in", 0, 0)) return false;
      if( DecodeStringChord( 15, 2, "on", 0, 0)) return false;
      if( DecodeStringChord( 15, 3, "ing", 0, 0)) return false;
      if( DecodeStringChord( 15, 4, "er", 0, 0)) return false;
      if( DecodePlainStringChord( 15, 6, "or", 0, 0)) return false;
      if( DecodeStringChord( 15, 8, "True", 0, 0)) return false;
      if( DecodeSpecialModeChord( 15, 15)) return false;
      return true;
    case 16:
      if( DecodeBaseChord( 16, 0, _BSP)) return false;
      if( DecodeTripleDotChord( 16, 7)) return false;
      if( DecodeStringChord( 16, 8, ";", 0, 1)) return false;
      if( DecodeCapitalChord( 16, 12, _RTN)) return false;
      if( DecodeKeypadChord( 16, 14, 0, 1, 5, 1)) return false;
      if( DecodeKeypadChord( 16, 15, 0, 1, 7, 6)) return false;
      if( DecodeLanguageChord( 16, 16)) return false;
      if( DecodeCapitalChord( 16, 24, _RTN)) return false;
      return true;
    case 17:
      if( DecodePlainStringChord( 17, 17, "#", 0, 0)) return false;
      return true;
    case 18:
      if( DecodePlainStringChord( 18, 2, "who", 0, 0)) return false;
      if( DecodePlainStringChord( 18, 6, "wh", 0, 0)) return false;
      return true;
    case 19:
      if( DecodePlainStringChord( 19, 1, " = ", 0, 0)) return false;
      return true;
    case 30:
      if( DecodeStringChord( 30, 16, "00", 0, 0)) return false;
      return true;
    case 31:
      if( DecodeWinChord( 31, 0)) return false;
      if( DecodeStringChord( 31, 16, "000", 0, 0)) return false;
      return true;
  }//switch
  return true;
}

//
// Decodes the pressed button for two-handed chords
// Returns true if further processing is not requred
//
bool DecodeBaseChord( int l, int r, char unshifted)
{
  if( left[1] != l) return false;
  if( right[1] != r) return false;
  if( space_L_Consumed)
  {
     space_L_Consumed = false;
     return true;
  }
  if( shift_Pressed) Keyboard_press( _SHIFT); 
  if( win_Requested) Keyboard_press( _GUI);
  Keyboard_write( unshifted);
  if( win_Requested) Keyboard_release( _GUI);
  if( shift_Pressed) Keyboard_release( _SHIFT); 
  ReleaseAllControls();
  return true;
}

//
// Decodes the pressed button for two-handed chords
// Returns true if further processing is not requred
// Makes substitutes '@' - '#' and '^' - '&' for correct show of Ъ and Ё
//
bool DecodeRussianChord( int l, int r, char unshifted, char shifted)
{
  if( left[1] != l) return false;
  if( right[1] != r) return false;
  if( shiftMode>0) Keyboard_write( shifted);
  else Keyboard_write( unshifted);
  ReleaseAllControls();
  if( shiftMode == 2) Keyboard_press(_SHIFT);
  return true;
}

//
// Decodes the pressed button for two-handed chords
// Returns true if further processing is not requred
// Outputs a string-sequience
//
bool DecodeStringChord( int l, int r, String s, int lefts, int enters)
{
  if( left[1] != l) return false;
  if( right[1] != r) return false;
  SendString( s, lefts, enters);
  return true;
}

//
// Decodes the pressed button for two-handed chords
// Returns true if further processing is not requred
// Outputs a string-sequience
//
bool DecodePlainStringChord( int l, int r, String s, int lefts, int enters)
{
  if( left[1] != l) return false;
  if( right[1] != r) return false;
  SendPlainString( s, lefts, enters);
  return true;
}

//
// Decodes the Win key request
// Returns true if further processing is not requred
//
bool DecodeWinChord( int l, int r)
{
  if( left[1] != l) return false;
  if( right[1] != r) return false;
  if( win_Requested)
  {
    Keyboard_press( _GUI);
    Keyboard_release( _GUI);
    win_Requested = false;
  }
  else
  {
    win_Requested = true;
  }
  return true;
}

//
// Decodes the triple-dot into a single char
// Returns true if further processing is not requred
//
bool DecodeTripleDotChord( int l, int r)
{
  if( left[1] != l) return false;
  if( right[1] != r) return false;
  Keyboard_release(_SHIFT);
  Keyboard_print( " ... ");
  Keyboard_write( _LEFT);  
  Keyboard_write( _LEFT);  
  Keyboard_write( _BSP);  
  Keyboard_write( _RIGHT);  
  Keyboard_write( _RIGHT);  
  if( shiftMode > 0) Keyboard_press(_SHIFT);
  return true;
}

//
// Decodes the scan codes for sending special characters
// The length must be 4 characters
//
bool DecodeKeypadChord( int l, int r, int a, int b, int c, int d)
{
  if( left[1] != l) return false;
  if( right[1] != r) return false;
  if( shiftMode > 0) Keyboard_release(_SHIFT);
  if( control_Pressed) Keyboard_release(_CTRL_R); 
  if( alt_Pressed) Keyboard_release(_ALT); 
  SendAltKeypad( a, b, c, d);
  if( alt_Pressed) Keyboard_press(_ALT); 
  if( control_Pressed) Keyboard_press(_CTRL_R); 
  if( shiftMode > 0) Keyboard_press(_SHIFT);
  return true;
}

//
// Decodes the language change chord
//
bool DecodeLanguageChord( int l, int r)
{
  if( left[1] != l) return false;
  if( right[1] != r) return false;
  SendRusLat();
  return true;
}

//
// Decodes double space for sending a capital letter after space or return
//
bool DecodeCapitalChord( int l, int r, int ch)
{
  if( left[1] != l) return false;
  if( right[1] != r) return false;
  Keyboard_write( ch);
  if( shiftMode == 0)
  {
    shiftMode = 1;
    Keyboard_press( _SHIFT);
  }
  return true;
}

//
// Decodes the pressed button
//
bool DecodeSpecialModeChord( int l, int r)
{
  if( left[1] != l) return false;
  if( right[1] != r) return false;
  specialMode++;
  if( specialMode > 3 ) specialMode = 0;
  return true;
}

//
// Decodes the special strokes
//
bool DecodeSpecialChord( int l, int r, String s0, String s1, String s2, int lefts, int enters)
{
  if( !special_Requested) return false;
  if( left[1] != l) return false;
  if( right[1] != r) return false;
  special_Requested = false;
  switch( specialMode )
  {
    case 1:
      SendString( s1, lefts, enters);
      return true;
    case 2:
      SendString( s2, lefts, enters);
      return true;
    default:
      SendString( s0, lefts, enters);
      break;
  }
  return true;
}

//
// Decodes the pressed button
//
void DecodeButtons( int n, const char Mapping[])
{
  if( n <= 0) return;
  if( n > 79) n = 79;
  char c = Mapping[n];
  if( c == _CH0) return;
  if( SendControl( c)) return;
  if( shift_Pressed) Keyboard_press( _SHIFT); 
  if( win_Requested) Keyboard_press( _GUI);
  Keyboard_write( c);
  if( win_Requested) Keyboard_release( _GUI);
  if( shift_Pressed) Keyboard_release( _SHIFT); 
  ReleaseAllControls();
}

//
// Sends a string with shift button and proper language
//
void SendString( String s, int lefts, int enters)
{
  char c;
  int len = s.length();
  if( len <= 0) return;
  Keyboard_write( s[0]);
  ReleaseAllControls();
  for( int i=1; i<len; i++)
  {
    c = s[i];
    if( c == '\n') Keyboard_release(_SHIFT);
    Keyboard_write( c);
    if( shiftMode > 0 && c == '\n') Keyboard_press(_SHIFT);    
  }
  Keyboard_release(_SHIFT);
  for( int i=0; i<lefts; i++) Keyboard_write( _LEFT);
  for( int i=0; i<enters; i++) Keyboard_write( _RTN);
  if( shiftMode > 0) Keyboard_press(_SHIFT);    
}

//
// Sends a string with shift button and proper language
//
void SendPlainString( String s, int lefts, int enters)
{
  char c;
  int len = s.length();
  if( len <= 0) return;
  ReleaseAllControls();
  if( shiftMode > 0) Keyboard_release(_SHIFT);
  if( control_Pressed) Keyboard_release(_CTRL_R); 
  if( alt_Pressed) Keyboard_release(_ALT); 
  for( int i=0; i<len; i++)
  {
    c = s[i];
    #ifdef _DEBUG
    Serial.print( "Character ");
    Serial.println( c);
    #endif
    //if( SubstituteCharacterToAlt(c)) continue;
    Keyboard_write( c);
  }
  for( int i=0; i<lefts; i++) Keyboard_write( _LEFT);
  for( int i=0; i<enters; i++) Keyboard_write( _RTN);
  if( alt_Pressed) Keyboard_press(_ALT); 
  if( control_Pressed) Keyboard_press(_CTRL_R); 
  if( shiftMode > 0) Keyboard_press(_SHIFT);
}

//
// Changes a character to an alt-sequence
//
bool SubstituteCharacterToAlt(char c)
{
  switch(c)
  {
    case '[':
      SendAltKeypad( 0, 0, 9, 1);
      return true;
    case ']':
      SendAltKeypad( 0, 0, 9, 3);
      return true;
    case '{':
      SendAltKeypad( 0, 1, 2, 3);
      return true;
    case '}':
      SendAltKeypad( 0, 1, 2, 5);
      return true;
    case '#':
      SendAltKeypad( 0, 0, 3, 5);
      return true;
    default:
      break;  
  }
  return false;
}

//
// Sends the scan codes
// The kp length must be 4 characters
//
void SendAltKeypad( int a, int b, int c, int d)
{
  Keyboard_press( _ALT);
  Keyboard_write( keypad_buttons[a]);
  Keyboard_write( keypad_buttons[b]);
  Keyboard_write( keypad_buttons[c]);
  Keyboard_write( keypad_buttons[d]);
  Keyboard_release( _ALT);
  #ifdef _DEBUG
  Serial.print( "ALT ");
  Serial.print( a);
  Serial.print( b);
  Serial.print( c);
  Serial.println( d);
  #endif
  delay(5);
}

//
// Converts button into a Control-Sequence
// Returns true if sent 
//
bool SendControl( char c)
{
  if( c == 'L')
  {
    if( !control_Pressed) Keyboard_press( _CTRL_R);
    Keyboard_write( _HOM);
    if( !control_Pressed) Keyboard_release( _CTRL_R);
    ReleaseAllControls();
    return true;
  }
  if( c == 'R')
  {
    if( !control_Pressed) Keyboard_press( _CTRL_R);
    Keyboard_write( _END);
    if( !control_Pressed) Keyboard_release( _CTRL_R);
    ReleaseAllControls();
    return true;
  }
  for( int i=0; i<26; i++)
  {
    if( c != ctrlKeys0[i]) continue;
    ReleaseAllControls();
    #ifdef _DEBUG
    Serial.print("Control - ");
    Serial.println(ctrlKeys1[i]);
    #endif
    if( shiftMode == 0 && shift_Pressed) Keyboard_press(_SHIFT);
    if( !control_Pressed) Keyboard_press(_CTRL_R);
    Keyboard_write( ctrlKeys1[i]);
    if( !control_Pressed) Keyboard_release(_CTRL_R);
    if( shiftMode == 0 && shift_Pressed) Keyboard_release(_SHIFT);
    ReleaseAllControls();
    return true;
  }
  return false;
}

//
// Releases Shift (mode 1), Win and Fun(mode 1) if engaged 
//
void ReleaseAllControls()
{
  win_Requested = false;
  if( shiftMode == 1)
  {
    shiftMode = 0;
    Keyboard_release( _SHIFT);
  }
  if( funMode == 1)
  {
    funMode = 0;
  }
}

//
// Low-level functions to read pins and set LEDs
//
//
// Reads a pin, returns the reading
//
int ReadPin( int i)
{
  if ( digitalRead(readPins[i]) == LOW) return 1;
  return 0;
}

//
// Reads a pin, returns the reading
//
int ReadPinLogical( int i)
{
  return digitalRead(readPins[i]) == LOW;
}

//
// Sets the LEDs based on the mode
//
void SetLEDs()
{
  long tm = millis();
  if( tm - LED_Blinker_Time > _BLINK_PERIOD)
  {
    LED_Blinker = !LED_Blinker;
    LED_Blinker_Time = tm;
  }
  SetLED( 0, shiftMode);
  SetLED( 1, funMode);
}

//
// Writes into one LED
//
void SetLED( int i, int mode)
{
  switch( mode)
  {
    case 0:
      digitalWrite(LEDPins[i], LOW);
      break;
    case 1:
      digitalWrite(LEDPins[i], HIGH);
      break;
    default:
      digitalWrite(LEDPins[i], LED_Blinker);
      break;
  }
}

//
// Writes to LEDs
//
void WriteLEDs( bool v1, bool v2)
{
  digitalWrite(LEDPins[0], v1);
  digitalWrite(LEDPins[1], v2);
}

//
// Low-level functions to handle keyboard outputs
//
void Keyboard_press(char key)
{
  #ifndef _DISABLE_KEYBOARD
  Keyboard.press( key);
  #endif
}

void Keyboard_write(char key)
{
  #ifndef _DISABLE_KEYBOARD
  Keyboard.write( key);
  #endif
}

void Keyboard_print(String s)
{
  #ifndef _DISABLE_KEYBOARD
  Keyboard.print( s);
  #endif
}

void Keyboard_release(char key)
{
  #ifndef _DISABLE_KEYBOARD
  Keyboard.release( key);
  #endif
}

void Mouse_set( bool v, int b)
{
  #ifndef _DISABLE_MOUSE
  bool p = Mouse.isPressed( b);
  if( v && !p) Mouse.press( b);
  if( !v && p) Mouse.release( b);
  #endif
}

void Mouse_move( signed char x, signed char y)
{
  if( x == 0 && y == 0) return;
  #ifndef _DISABLE_MOUSE
  Mouse.move( x, y, _NULLMOUSE);
  #endif
}

void Mouse_scroll( signed char w, int wait)
{
  if( w == 0) return;
  #ifndef _DISABLE_MOUSE
  Mouse.move( _NULLMOUSE, _NULLMOUSE, w);
  #endif
  delay( wait);
}

//
// Normalizes joystick reading to -1 to 1 range
//
void NormalizeJoystickToOne( int i)
{
  signed char p = pot_Position[i];
  if( p<0) pot_Position[i] = _MINUSMOUSE;
  if( p==0) pot_Position[i] = _NULLMOUSE;
  if( p>0) pot_Position[i] = _PLUSMOUSE;
}

//
// Normalizes joystick to ballistic response
//
void NormalizeJoystickBallistic( int i, int data)
{
  signed char p = pot_Position[i];
  if( data < pot_Middle[i])
    data = map(data, pot_Low[i], pot_Middle[i], pot_Calibrated_Low[i], 0);
  else
    data = map(data, pot_Middle[i], pot_High[i],  0, pot_Calibrated_High[i]);
  if( data < -10)
  {
    if( p > 0) pot_Position[i] = _NULLMOUSE; 
    if( p > -data*data/20) pot_Position[i]-=2; 
  }
  if( -10 <= data && data < -4) pot_Position[i] = _MINUSMOUSE;
  if( -4 <= data && data <= 4) pot_Position[i] = _NULLMOUSE;
  if( 4 < data && data <= 10) pot_Position[i] = _PLUSMOUSE;
  if( 10 < data)
  {
    if( p < 0) pot_Position[i] = _NULLMOUSE; 
    if( p < data*data/20) pot_Position[i]+=2; 
  }
}

//
// Changes between Rus and Lat by pressing and releasing left pedal or double shift
//
void SendRusLat()
{
  BasicRusLat();
}

//
// Implements basic Rus-Lat sequence
//
void BasicRusLat()
{
  if( control_Pressed) Keyboard_release( _CTRL_R);
  if( alt_Pressed) Keyboard_release( _ALT);
  if( shiftMode == 0) Keyboard_press( _SHIFT);
  Keyboard_press(_CTRL);
  Keyboard_press(_GUI);
  delay(3);
  Keyboard_write(' ');
  delay(3);
  Keyboard_release(_GUI);
  Keyboard_release(_CTRL);
  if( shiftMode == 0) Keyboard_release( _SHIFT);
  if( alt_Pressed) Keyboard_press( _ALT);
  if( control_Pressed) Keyboard_press( _CTRL_R);
}
