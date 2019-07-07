//
// 21-button input method for stationary chorded keyboard with 2 PSP joysticks
// Left hand: 4 finger buttons and 3 mouse buttons
// Right hand: 4 finger buttons and 4 arrow buttons
// Left thumb: BACK, Shift, Control
// Right thumb: SPACE, Function, Alt
// v 9.0 04-Jul-2019
// Tested with Arduino IDE 1.8.9
// Set the board to Arduiono/Genuino Micro
// This work is public domain under GNU licence
//

// Uncomment for serial debugging
//#define _DEBUG
//#define _DEBUG_MOUSE
//#define _DEBUG_KEYBOARD

// Uncomment to disable hardware while debugging
//#define _DISABLE_MOUSE
//#define _DISABLE_KEYBOARD

#include <Keyboard.h>
#include <Mouse.h>
#include "keys.h"
#include "macros.h"
#include "keyjoy.h"

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
