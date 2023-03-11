#include "TinyStepper_28BYJ_48.h"
#include <EEPROM.h>

extern bool bluetooth_F1, bluetooth_F2, bluetooth_F3, bluetooth_F4, bluetooth_F5, bluetooth_F6;

TinyStepper_28BYJ_48 stepper1;
int BinState;
int StepsPerRound;
int cells;
bool KeyBinState;
int stepi;
int screenEnt;
int screenOk;

void setup() {
  BTinit();
  stepper1.connectToPins(8, 9, 10, 11);
  stepper1.setSpeedInStepsPerSecond(256);
  KeyBinState = 0;
  StepsPerRound = 64 * 32;
  cells = (StepsPerRound / 9 + 48) * 6;
  stepi = 0;
  EEPROM.update(0, 3);
  Serial1.begin(9600);
}

void stepr(int s) {
  stepper1.moveRelativeInSteps(s * cells);
}

void loop() {
  BinState = EEPROM.read(0);
  screenEnt = Serial1.parseInt();
  if (screenEnt != 0) {
    screenOk = screenEnt;
  }

  if (screenOk == 7) {
    stepr(-1);
    BinState = BinState - 1;
    if (BinState == 0) {
      BinState = 6;
    }
    EEPROM.update(0, BinState);
    screenOk = 0;
  }
  
  if (screenOk == 8) {
    stepr(1);
    BinState = BinState + 1;
    if (BinState == 7) {
      BinState = 1;
    }
    EEPROM.update(0, BinState);
    screenOk = 0;
  }

  if (screenOk == 1) {
    BinState = EEPROM.read(0);
    if (BinState == 2) {
      stepr(2);
    } else if (BinState == 3) {
      stepr(2);
    } else if (BinState == 4) {
      stepr(3);
    } else if (BinState == 5) {
      stepr(-2);
    } else if (BinState == 6) {
      stepr(-1);
    }
    EEPROM.update(0, 1);
    delay(200);
  }
  if (screenOk == 2) {
    BinState = EEPROM.read(0);
    if (BinState == 1) {
      stepr(-1);
    } else if (BinState == 3) {
      stepr(1);
    } else if (BinState == 4) {
      stepr(2);
    } else if (BinState == 5) {
      stepr(-3);
    } else if (BinState == 6) {
      stepr(2);
    }
    EEPROM.update(0, 2);
    delay(200);
  }
  if (screenOk == 3) {
    BinState = EEPROM.read(0);
    if (BinState == 1) {
      stepr(-2);
    } else if (BinState == 2) {
      stepr(-1);
    } else if (BinState == 4) {
      stepr(3);
    } else if (BinState == 5) {
      stepr(2);
    } else if (BinState == 6) {
      stepr(-3);
    }
    EEPROM.update(0, 3);
    delay(200);
  }
  if (screenOk == 4) {
    BinState = EEPROM.read(0);
    if (BinState == 1) {
      stepr(-3);
    } else if (BinState == 2) {
      stepr(-2);
    } else if (BinState == 3) {
      stepr(-1);
    } else if (BinState == 5) {
      stepr(1);
    } else if (BinState == 6) {
      stepr(2);
    }
    EEPROM.update(0, 4);
    delay(200);
  }
  if (screenOk == 5) {
    BinState = EEPROM.read(0);
    if (BinState == 1) {
      stepr(2);
    } else if (BinState == 2) {
      stepr(3);
    } else if (BinState == 3) {
      stepr(-2);
    } else if (BinState == 4) {
      stepr(-1);
    } else if (BinState == 6) {
      stepr(1);
    }
    EEPROM.update(0, 5);
    delay(200);
  }
  if (screenOk == 6) {
    BinState = EEPROM.read(0);
    if (BinState == 1) {
      stepr(1);
    } else if (BinState == 2) {
      stepr(-2);
    } else if (BinState == 3) {
      stepr(3);
    } else if (BinState == 4) {
      stepr(-2);
    } else if (BinState == 5) {
      stepr(-1);
    }
    EEPROM.update(0, 6);
    delay(200);
  }

}
