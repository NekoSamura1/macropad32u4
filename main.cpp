#include <Arduino.h>
#include <EEPROM.h>
#include <Arduino_ST7789_Fast.h>
#include <Keyboard.h>
#include <Mouse.h>

#define OFFSETDELAY 20
// ButtonPAD----------------------------------------------------------------------------------------ButtonPAD
#define C1 5 // layout could differ
#define C2 4
#define C3 3
#define C4 2
#define R1 6
#define R2 7
#define R3 8
#define R4 9
void buttonPadInit();
uint16_t buttonPadState();

// Display--------------------------------------------------------------------------------------------Display
#define TFT_DC A1
#define TFT_RST A0
#define TFT_BL A2
#define SCR_WD 240
#define SCR_HT 240
Arduino_ST7789 lcd = Arduino_ST7789(TFT_DC, TFT_RST);
void displayInit();
void displayUpdate();
uint16_t displayState;
uint8_t sleepTimer = 0;
// EEPROMString----------------------------------------------------------------------------------EEPROMString
bool writeSavedString(uint8_t stringNumber);
void superSecret();
// Macro------------------------------------------------------------------------------------------------Macro
void macro(uint16_t buttonState);
uint16_t macroState = 0;

#define LMBspam 0
#define RMBspam 1
#define LMBspamHold 2
#define RMBspamHold 3
#define LMBhold 4
#define RMBhold 5
#define Whold 6
#define SpaceHold 7
#define GIartifact 8
// #define UNKNOWN9 9  //undefined
// #define UNKNOWN9 10 //removed as unnecessary due to quol patch
// #define UNKNOWN9 11 //removed as unnecessary due to quol patch
// #define UNKNOWN12 12  //undefined
// #define UNKNOWN13 13  //undefined
#define POWERSHELL 14
#define ALLOFF 15

uint16_t macroStateCnanged = 0; // было ли на этом нажатии кнопки изменено состояние макроса
uint16_t keyState = 0;          // нажата ли сейчас кнопка

void setup()
{
  Keyboard.begin();
  Mouse.begin();
  buttonPadInit();
  displayInit();
  pinMode(A3, INPUT_PULLUP); // mode switch
}

void loop()
{
  // uint16_t buttonState = buttonPadState();
  if (digitalRead(A3))
    macro(buttonPadState());
  else
    superSecret();

  if (sleepTimer > 250)
  { // выключить дисплей, если он долго не использовался
    lcd.enableDisplay(false);
    digitalWrite(TFT_BL, LOW);
  }
  else if (!macroState) // отсчет таймера сна с момента выключеняи всех макросов
    sleepTimer++;
  delay(OFFSETDELAY);
}

void yield()
{
  displayUpdate();
}

void buttonPadInit()
{
  pinMode(R1, INPUT_PULLUP);
  pinMode(R2, INPUT_PULLUP);
  pinMode(R3, INPUT_PULLUP);
  pinMode(R4, INPUT_PULLUP);
}

uint16_t buttonPadState()
{
  uint16_t buttonState = 0;

  pinMode(C1, OUTPUT);
  digitalWrite(C1, 0);
  if (digitalRead(R1) == 0)
    buttonState |= 1 << 0;
  if (digitalRead(R2) == 0)
    buttonState |= 1 << 1;
  if (digitalRead(R3) == 0)
    buttonState |= 1 << 2;
  if (digitalRead(R4) == 0)
    buttonState |= 1 << 3;
  pinMode(C1, INPUT);

  pinMode(C2, OUTPUT);
  digitalWrite(C2, 0);
  if (digitalRead(R1) == 0)
    buttonState |= 1 << 4;
  if (digitalRead(R2) == 0)
    buttonState |= 1 << 5;
  if (digitalRead(R3) == 0)
    buttonState |= 1 << 6;
  if (digitalRead(R4) == 0)
    buttonState |= 1 << 7;
  pinMode(C2, INPUT);

  pinMode(C3, OUTPUT);
  digitalWrite(C3, 0);
  if (digitalRead(R1) == 0)
    buttonState |= 1 << 8;
  if (digitalRead(R2) == 0)
    buttonState |= 1 << 9;
  if (digitalRead(R3) == 0)
    buttonState |= 1 << 10;
  if (digitalRead(R4) == 0)
    buttonState |= 1 << 11;
  pinMode(C3, INPUT);

  pinMode(C4, OUTPUT);
  digitalWrite(C4, 0);
  if (digitalRead(R1) == 0)
    buttonState |= 1 << 12;
  if (digitalRead(R2) == 0)
    buttonState |= 1 << 13;
  if (digitalRead(R3) == 0)
    buttonState |= 1 << 14;
  if (digitalRead(R4) == 0)
    buttonState |= 1 << 15;
  pinMode(C4, INPUT);

  return buttonState;
}

bool writeSavedString(uint8_t stringNumber)
{
  //---------------------------------------------------------------------------
  uint8_t stringNumberCurr = 0;
  uint16_t memAddres = 0;
  while (stringNumber > stringNumberCurr++)
  {
    if (EEPROM.read(memAddres) == 0xFF)
      return 1;
    else
      memAddres += EEPROM.read(memAddres++);
  }
  uint8_t stringLength = EEPROM.read(memAddres++);
  char readStr[stringLength];
  for (uint8_t i = 0; i < stringLength; i++)
    readStr[i] = EEPROM.read(memAddres++);
  //---------------------------------------------------------------------------
  for (uint8_t i = 0; i < sizeof(readStr); i++)
    Keyboard.write(readStr[i]);
  delay(500);
  return 0;
}

void displayInit()
{
  lcd.init(SCR_WD, SCR_HT);
  lcd.fillScreen(BLACK);
  lcd.setCursor(22, 0);
  lcd.setTextColor(WHITE);
  lcd.setTextSize(3);
  lcd.print("MACRO STATE");
  displayUpdate();
  pinMode(TFT_BL, OUTPUT);
  displayState = ~macroState;
  displayUpdate();
}

void displayUpdate()
{
  if (macroState != displayState)
  {
    digitalWrite(TFT_BL, HIGH);
    lcd.enableDisplay(true);
    for (uint8_t i = 0; i < 4; i++)
      for (uint8_t j = 0; j < 4; j++)
        if (macroState & 1 << (i + j * 4))
          lcd.drawCircle(44 + i * 50, 54 + j * 50, 24, GREEN);
        else
          lcd.drawCircle(44 + i * 50, 54 + j * 50, 24, RED);
    displayState = macroState;
    sleepTimer = 0;
  }
}

void superSecret()
{
  switch (buttonPadState())
  {
  case 0b0100000000010010:
    writeSavedString(0);
    break;
  case 0b1000000000010010:
    writeSavedString(1);
    break;
  case 0b0010000000010010:
    writeSavedString(2);
    break;
  case 0b0100000000010100:
    writeSavedString(3);
    break;
  case 0b1000000000010100:
    writeSavedString(4);
    break;

  default:
    break;
  }
}

void powershellCall()
{
  Keyboard.press(KEY_LEFT_GUI);
  delay(10);
  Keyboard.write('r');
  delay(10);
  Keyboard.release(KEY_LEFT_GUI);
  delay(200);
  Keyboard.print("powershell");
  delay(100);
  Keyboard.write(KEY_RETURN);
}

void macro(uint16_t buttonState)
{
  //  macroupdate = macroState;

  if (buttonState & 1 << LMBspam)
  { //                                                    lmb spam
    macroState |= 1 << LMBspam;
    Mouse.click(MOUSE_LEFT);
  }
  else
    macroState &= ~(1 << LMBspam);

  if (buttonState & 1 << RMBspam)
  { //                                                    rmb spam
    macroState |= 1 << RMBspam;
    Mouse.click(MOUSE_RIGHT);
  }
  else
    macroState &= ~(1 << RMBspam);

  if (buttonState & 1 << LMBspamHold)
  { //                                                 lmb spam toggle
    if (!(macroStateCnanged & 1 << LMBspamHold))
    {
      macroState ^= 1 << LMBspamHold;
      macroStateCnanged |= 1 << LMBspamHold;
    }
  }
  else
    macroStateCnanged &= ~(1 << LMBspamHold);
  if (macroState & 1 << LMBspamHold)
    Mouse.click(MOUSE_LEFT);

  if (buttonState & 1 << RMBspamHold)
  { //                                                 rmb spam toggle
    if (!(macroStateCnanged & 1 << RMBspamHold))
    {
      macroState ^= 1 << RMBspamHold;
      macroStateCnanged |= 1 << RMBspamHold;
    }
  }
  else
    macroStateCnanged &= ~(1 << RMBspamHold);
  if (macroState & 1 << RMBspamHold)
    Mouse.click(MOUSE_RIGHT);

  if (buttonState & 1 << LMBhold)
  { //                                                 lmb hold toggle
    if (!(macroStateCnanged & 1 << LMBhold))
    {
      macroState ^= 1 << LMBhold;
      macroStateCnanged |= 1 << LMBhold;
      if ((macroState & 1 << LMBhold))
      {
        Mouse.press(MOUSE_LEFT);
        keyState |= 1 << LMBhold;
      }
    }
  }
  else
    macroStateCnanged &= ~(1 << LMBhold);

  if (!(macroState & 1 << LMBhold) && (keyState & 1 << LMBhold))
  {
    Mouse.release(MOUSE_LEFT);
    keyState &= ~(1 << LMBhold);
  }

  if (buttonState & 1 << RMBhold)
  { //                                                 rmb hold toggle
    if (!(macroStateCnanged & 1 << RMBhold))
    {
      macroState ^= 1 << RMBhold;
      macroStateCnanged |= 1 << RMBhold;
      if ((macroState & 1 << RMBhold))
      {
        Mouse.press(MOUSE_RIGHT);
        keyState |= 1 << RMBhold;
      }
    }
  }
  else
    macroStateCnanged &= ~(1 << RMBhold);
  if (!(macroState & 1 << RMBhold) && (keyState & 1 << RMBhold))
  {
    Mouse.release(MOUSE_RIGHT);
    keyState &= ~(1 << RMBhold);
  }

  if (buttonState & 1 << Whold)
  { //                                                 w hold toggle
    if (!(macroStateCnanged & 1 << Whold))
    {
      macroState ^= 1 << Whold;
      macroStateCnanged |= 1 << Whold;
      if ((macroState & 1 << Whold))
      {
        Keyboard.press('w');
        keyState |= 1 << Whold;
      }
    }
  }
  else
    macroStateCnanged &= ~(1 << Whold);
  if (!(macroState & 1 << Whold) && (keyState & 1 << Whold))
  {
    Keyboard.release('w');
    keyState &= ~(1 << Whold);
  }
  if (buttonState & 1 << SpaceHold)
  { //                                                   space spam toggle
    if (!(macroStateCnanged & 1 << SpaceHold))
    {
      macroState ^= 1 << SpaceHold;
      macroStateCnanged |= 1 << SpaceHold;
    }
  }
  else
    macroStateCnanged &= ~(1 << SpaceHold);
  if (macroState & 1 << SpaceHold)
    Keyboard.write(0x20);

  macroState &= ~(1 << GIartifact); //                                                      gi artifact 2.3
  if (buttonState & 1 << GIartifact)
  {
    macroState |= 1 << GIartifact;
    // macroupdate = 1;
    for (uint8_t i = 0; i < 41; i++)
      Mouse.move(-127, -127);
    for (uint8_t i = 0; i < 35; i++)
      Mouse.move(127, 58);
    delay(20);
    Mouse.click(); // авто
    delay(20);
    for (uint8_t i = 0; i < 6; i++)
      Mouse.move(0, 127);
    delay(20);
    Mouse.click(); // вкачать
    delay(20);
    for (uint8_t i = 0; i < 33; i++)
      Mouse.move(-127, -71);
    delay(20);
    Mouse.click(); // детали
    delay(20);
    Mouse.move(0, 100);
    delay(300);
    Mouse.click(); // улучшить
  }

  macroState &= ~(1 << POWERSHELL); //                                                      powershell 4.3
  if (buttonState & 1 << POWERSHELL)
  {
    macroState |= 1 << POWERSHELL;
    // macroupdate = 1;
    powershellCall();
  }

  macroState &= ~(1 << ALLOFF); //                                                        OFF OFF OFF OFF 4.4
  if (buttonState & 1 << ALLOFF)
  {
    macroState = 1 << ALLOFF;
  }
}
