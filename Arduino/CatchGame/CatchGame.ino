static const int BLINK_DELAY = 250;

/* This array contains all relevant information regarding the state of the board. Each element contains the pin number and the state of an LED. The row and column number reflects the physical position of the LED. */
static const int BOARD_ROWS = 3;
static const int BOARD_COLS = 2;
int board[BOARD_ROWS][BOARD_COLS][2] = {
  {{6, LOW}, {7, LOW}},
  {{4, LOW}, {5, LOW}},
  {{2, LOW}, {3, LOW}}
};

static int playerPosition[] = {2, 0};
static int objectivePosition[] = {0, 0};

// write HIGH or LOW to all LEDS
static void writeAllPins(int state);

// draw the board using the board array
static void drawBoard(void);

// the setup is just for show
void setup() {
  // light up each LED, one at a time
  for (size_t i = 0; i < BOARD_ROWS; i++) {
    for (size_t j = 0; j < BOARD_COLS; j++) {
      board[i][j][1] = HIGH; //digitalWrite(PIN_MAP[i][j], HIGH);
      drawBoard();
      delay(BLINK_DELAY);
    }
  }

  // blink all LEDs a few times
  for (size_t k = 0; k < 5; k++) {
    writeAllPins(HIGH);
    delay(BLINK_DELAY);
    writeAllPins(LOW);
    delay(BLINK_DELAY);
  }

  // test drawBoard()
  writeAllPins(LOW);
  delay(500);
  board[2][1][1] = HIGH;
  board[0][0][1] = HIGH;
  drawBoard();
}

void loop() {
  // put your main code here, to run repeatedly:

}

static void writeAllPins(int state) {
  for (size_t i = 0; i < BOARD_ROWS; i++) {
    for (size_t j = 0; j < BOARD_COLS; j++) {
      board[i][j][1] = state;
      drawBoard();
    }
  }
}

static void drawBoard(void) {
  for (size_t i = 0; i < BOARD_ROWS; i++) {
    for (size_t j = 0; j < BOARD_COLS; j++) {
      digitalWrite(board[i][j][0], board[i][j][1]);
    }
  }
}

