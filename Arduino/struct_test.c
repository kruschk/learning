struct led {
  int pin;
  int state;
} led_table[2][3];

//struct led led_table[2][3];

int table[3][3] = {
  0, 0, 0,
  0, 0, 0,
  0, 0, 0
};

struct board {
  int table[3][3];
  int state[3][3];
};

struct window {
  const int pin_number[2][3];
  int pin_state[2][3];
};

struct window game_window = {
  { 6,   7,
    4,   5,
    2,   3 },
  { LOW, LOW,
    LOW, LOW,
    LOW, LOW }
};