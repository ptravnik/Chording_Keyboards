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
// Implements basic Rus-Lat sequence for Windows 10
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
