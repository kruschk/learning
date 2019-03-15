#include <string.h>

char inputString[] = "SOS"; // change this line to change the message!
const unsigned int PINNUMBER = 5;
const unsigned int DOT_TIME = 64; // the time for a tone
const unsigned int DASH_TIME = 3*DOT_TIME;
const unsigned int TIME_BETWEEN_DOT_DASH = DOT_TIME;
const unsigned int TIME_BETWEEN_CHARS = 3*DOT_TIME - TIME_BETWEEN_DOT_DASH; // accounts for dot-dash time (check if correct)
const unsigned int TIME_BETWEEN_WORDS = 7*DOT_TIME - TIME_BETWEEN_CHARS - TIME_BETWEEN_DOT_DASH; // accounts for char and dot-dash time (check if correct)
const size_t strLen = strlen(inputString); // get the length of the input string

void setup() {
  // iterate through characters in the array and change them to lowercase
  for (size_t i = 0; i < strLen; i++) {
    inputString[i] = tolower(inputString[i]);
  }

  // set output pin to PINNUMBER (defined above) and make sure it's set to low
  pinMode(PINNUMBER,OUTPUT); 
  analogWrite(PINNUMBER,LOW);
}

// iterates through each character in the input string, calling a combination of dot() or dash() representing the character.
void loop() {
  // for each element in the string...
  for (size_t i = 0; i < strLen; i++) {
    // switch-case to determine character and output morse code
    switch (inputString[i]) {
      case 'a':
        dot();
        dash();
        break;
      case 'b':
        dash();
        dot();
        dot();
        dot();
        break;
      case 'c':
        dash();
        dot();
        dash();
        dot();
        break;
      case 'd':
        dash();
        dot();
        dot();
        break;
      case 'e':
        dot();
        break;
      case 'f':
        dot();
        dot();
        dash();
        dot();
        break;
      case 'g':
        dash();
        dash();
        dot();
        break;
      case 'h':
        dot();
        dot();
        dot();
        dot();
        break;
      case 'i':
        dot();
        dot();
        break;
      case 'j':
        dot();
        dash();
        dash();
        dash();
        break;
      case 'k':
        dash();
        dot();
        dash();
        break;
      case 'l':
        dot();
        dash();
        dot();
        dot();
        break;
      case 'm':
        dash();
        dash();
        break;
      case 'n':
        dash();
        dot();
        break;
      case 'o':
        dash();
        dash();
        dash();
        break;
      case 'p':
        dot();
        dash();
        dash();
        dot();
        break;
      case 'q':
        dash();
        dash();
        dot();
        dash();
        break;
      case 'r':
        dot();
        dash();
        dot();
        break;
      case 's':
        dot();
        dot();
        dot();
        break;
      case 't':
        dash();
        break;
      case 'u':
        dot();
        dot();
        dash();
        break;
      case 'v':
        dot();
        dot();
        dot();
        dash();
        break;
      case 'w':
        dot();
        dash();
        dash();
        break;
      case 'x':
        dash();
        dot();
        dot();
        dash();
        break;
      case 'y':
        dash();
        dot();
        dash();
        dash();
        break;
      case 'z':
        dash();
        dash();
        dot();
        dot();
        break;
      case ' ':
        delay(TIME_BETWEEN_WORDS);
        break;
      case '0':
        dash();
        dash();
        dash();
        dash();
        dash();
        break;
      case '1':
        dot();
        dash();
        dash();
        dash();
        dash();
        break;
      case '2':
        dot();
        dot();
        dash();
        dash();
        dash();
        break;
      case '3':
        dot();
        dot();
        dot();
        dash();
        dash();
        break;
      case '4':
        dot();
        dot();
        dot();
        dot();
        dash();
        break;
      case '5':
        dot();
        dot();
        dot();
        dot();
        dot();
        break;
      case '6':
        dash();
        dot();
        dot();
        dot();
        dot();
        break;
      case '7':
        dash();
        dash();
        dot();
        dot();
        dot();
        break;
      case '8':
        dash();
        dash();
        dash();
        dot();
        dot();
        break;
      case '9':
        dash();
        dash();
        dash();
        dash();
        dot();
        break;
      case '.':
        dot();
        dash();
        dot();
        dash();
        dot();
        dash();
        break;
      case ',':
        dash();
        dash();
        dot();
        dot();
        dash();
        dash();
        break;
      case ':':
        dash();
        dash();
        dash();
        dot();
        dot();
        dot();
        break;
      case '?':
        dot();
        dot();
        dash();
        dash();
        dot();
        dot();
        break;
      case '\'':
        dot();
        dash();
        dash();
        dash();
        dash();
        dot();
        break;
      case '-':
        dash();
        dot();
        dot();
        dot();
        dot();
        dash();
        break;
      case '/':
        dash();
        dot();
        dot();
        dash();
        dot();
        break;
      case '\"':
        dot();
        dash();
        dot();
        dot();
        dash();
        dot();
        break;
      case '@':
        dot();
        dash();
        dash();
        dot();
        dash();
        dot();
        break;
      case '=':
        dash();
        dot();
        dot();
        dot();
        dash();
        break;
      default:
        delay(TIME_BETWEEN_CHARS);
        break;
    }
    delay(TIME_BETWEEN_CHARS);
  }
  delay(2500);
}

// dot function, sets output pin to high (represents a dot in morse code)
void dot() {
  analogWrite(PINNUMBER,HIGH);
  delay(DOT_TIME);
  analogWrite(PINNUMBER,LOW);
  delay(TIME_BETWEEN_DOT_DASH);
}

// dash function, sets output pin to high (represents a dash in morse code)
void dash() {
  analogWrite(PINNUMBER,HIGH);
  delay(DASH_TIME);
  analogWrite(PINNUMBER,LOW);
  delay(TIME_BETWEEN_DOT_DASH);
}
