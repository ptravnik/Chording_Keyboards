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
      if( DecodeStringChord( 11, 1, _MACRO_1, 0, 0)) return false;
      if( DecodeStringChord( 11, 2, _MACRO_2, 0, 0)) return false;
      if( DecodeStringChord( 11, 3, _MACRO_3, 0, 0)) return false;
      if( DecodeStringChord( 11, 4, _MACRO_4, 0, 0)) return false;
      if( DecodeStringChord( 11, 5, _MACRO_5, 0, 0)) return false;
      if( DecodeStringChord( 11, 6, _MACRO_6, 0, 0)) return false;
      if( DecodeStringChord( 11, 7, _MACRO_7, 0, 0)) return false;
      if( DecodeStringChord( 11, 8, _MACRO_8, 0, 0)) return false;
      if( DecodeStringChord( 11, 9, _MACRO_9, 0, 0)) return false;
      if( DecodeStringChord( 11, 10, _MACRO_10, 0, 0)) return false;
      if( DecodeStringChord( 11, 11, _MACRO_11, 0, 0)) return false;
      if( DecodeStringChord( 11, 12, _MACRO_12, 0, 0)) return false;
      if( DecodeStringChord( 11, 13, _MACRO_13, 0, 0)) return false;
      if( DecodeStringChord( 11, 14, _MACRO_14, 0, 0)) return false;
      if( DecodeStringChord( 11, 15, _MACRO_15, 0, 0)) return false;
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
