#include <Arduino_ST7789_Fast.h>
#include <Keyboard.h>
#include <Mouse.h>

#define TFT_DC A1 //display pins
#define TFT_RST A0
#define SCR_WD 240
#define SCR_HT 240
Arduino_ST7789 lcd = Arduino_ST7789(TFT_DC, TFT_RST);

#define c1 5 // change them if the layout of the buttons does not match the display on the screen
#define c2 4
#define c3 3
#define c4 2
#define r1 9
#define r2 8
#define r3 7
#define r4 6

#define DELAYOFFSET 30 // increase if your app or pc does not support too fast clicks

uint16_t macroupdate = 1;
uint16_t buttonstate = 0;
uint16_t macrostate = 0;
uint16_t macrocng = 0;

#define CLICKDELAY  50
#define EXTENDELAY 400
void exphelper(){  
  for (uint8_t i = 0; i < 41; i++) Mouse.move(-127, -127);
  for (uint8_t i = 0; i < 40; i++) Mouse.move(124, 67);
  delay(CLICKDELAY);  
  Mouse.click(); //сбор
  delay(EXTENDELAY);   
  Mouse.click(); //подтверждение сбора
  delay(EXTENDELAY);  
  Mouse.click(); //выбор персонажа
  delay(EXTENDELAY); 
}

// void expeditions(){
//   for (uint8_t i = 0; i < 41; i++) Mouse.move(-127, -127);//--------------------------------------------------------------МОНД
//   for (uint8_t i = 0; i < 4; i++) Mouse.move(48, 120);
//   delay(CLICKDELAY);
//   Mouse.click(); //мондштадт 
//   delay(CLICKDELAY);
//   for (uint8_t i = 0; i < 20; i++) Mouse.move(127, 20);
//   delay(CLICKDELAY);  
//   Mouse.click(); //выбор 1 эксп
//   delay(CLICKDELAY); 
//   exphelper();  //----------------------------------------------сбор
//   for (uint8_t i = 0; i < 21; i++) Mouse.move(-127, -108);
//   delay(CLICKDELAY);  
//   Mouse.click(); //выбор беннета
//   delay(CLICKDELAY);
//   for (uint8_t i = 0; i < 11; i++) Mouse.move(81, 125);  
//   delay(EXTENDELAY);
//   Mouse.click(); //выбор 2 эксп
//   delay(CLICKDELAY);
//   exphelper();  //----------------------------------------------сбор
//   for (uint8_t i = 0; i < 21; i++) Mouse.move(-127, -97);
//   delay(CLICKDELAY);  
//   Mouse.click(); //выбор фишки
//   delay(CLICKDELAY);
//   for (uint8_t i = 0; i < 41; i++) Mouse.move(-127, -127);//--------------------------------------------------------------ЛИЮЭ 
//   for (uint8_t i = 0; i < 5; i++) Mouse.move(37, 120);
//   delay(EXTENDELAY);
//   Mouse.click(); //ЛИЮЭ 
//   delay(CLICKDELAY);
//   for (uint8_t i = 0; i < 20; i++) Mouse.move(120, 33);
//   delay(CLICKDELAY);  
//   Mouse.click(); //выбор 1 эксп
//   delay(CLICKDELAY);  
//   exphelper();  //----------------------------------------------сбор 
//   for (uint8_t i = 0; i < 21; i++) Mouse.move(-127, -85);
//   delay(CLICKDELAY);  
//   Mouse.click(); //выбор Елань
//   delay(CLICKDELAY);
//   for (uint8_t i = 0; i < 4; i++) Mouse.move(-30, 127);  
//   delay(EXTENDELAY);
//   Mouse.click(); //выбор 2 эксп
//   delay(CLICKDELAY);
//   exphelper();  //----------------------------------------------сбор
//   for (uint8_t i = 0; i < 21; i++) Mouse.move(-127, -97);
//   delay(CLICKDELAY);  
//   Mouse.click(); //выбор Кекинг
//   delay(CLICKDELAY);

//   for (uint8_t i = 0; i < 41; i++) Mouse.move(-127, -127);//--------------------------------------------------------------ЯПОНИЯ
//   for (uint8_t i = 0; i < 6; i++) Mouse.move(32, 127);
//   delay(EXTENDELAY);
//   Mouse.click(); //япония
//   delay(CLICKDELAY);
//   for (uint8_t i = 0; i < 20; i++) Mouse.move(127, -8);
//   delay(CLICKDELAY);  
//   Mouse.click(); //выбор 1 эксп
//   exphelper();  //----------------------------------------------сбор
//   for (uint8_t i = 0; i < 21; i++) Mouse.move(-127, -97);
//   delay(CLICKDELAY);  
//   Mouse.click(); //выбор кукихи
// }

void expeditions12h(){
  for (uint8_t i = 0; i < 41; i++) Mouse.move(-127, -127);//--------------------------------------------------------------МОНД
  for (uint8_t i = 0; i < 4; i++) Mouse.move(48, 120);
  delay(CLICKDELAY);
  Mouse.click(); //мондштадт 
  delay(CLICKDELAY);
  for (uint8_t i = 0; i < 20; i++) Mouse.move(127, 20);
  delay(CLICKDELAY);  
  Mouse.click(); //выбор 1 эксп
  delay(CLICKDELAY); 
  exphelper();  //----------------------------------------------сбор
  for (uint8_t i = 0; i < 21; i++) Mouse.move(-127, -108);
  delay(CLICKDELAY);  
  Mouse.click(); //выбор беннета
  delay(CLICKDELAY);
  for (uint8_t i = 0; i < 11; i++) Mouse.move(81, 125);  
  delay(EXTENDELAY);
  Mouse.click(); //выбор 2 эксп
  delay(CLICKDELAY);
  exphelper();  //----------------------------------------------сбор
  for (uint8_t i = 0; i < 21; i++) Mouse.move(-127, -97);
  delay(CLICKDELAY);  
  Mouse.click(); //выбор фишки
  delay(CLICKDELAY);
  for (uint8_t i = 0; i < 41; i++) Mouse.move(-127, -127);//--------------------------------------------------------------ЛИЮЭ 
  for (uint8_t i = 0; i < 5; i++) Mouse.move(37, 120);
  delay(EXTENDELAY);
  Mouse.click(); //ЛИЮЭ 
  delay(CLICKDELAY);
  for (uint8_t i = 0; i < 4; i++) Mouse.move(-30, 127);  
  delay(EXTENDELAY);
  Mouse.click(); //выбор 2 эксп
  delay(CLICKDELAY);
  exphelper();  //----------------------------------------------сбор
  for (uint8_t i = 0; i < 21; i++) Mouse.move(-127, -97);
  delay(CLICKDELAY);  
  Mouse.click(); //выбор Кекинг
  delay(CLICKDELAY);
}

void expeditions20h(){
  for (uint8_t i = 0; i < 41; i++) Mouse.move(-127, -127);//--------------------------------------------------------------ЛИЮЭ 
  for (uint8_t i = 0; i < 5; i++) Mouse.move(37, 120);
  delay(EXTENDELAY);
  Mouse.click(); //ЛИЮЭ 
  delay(CLICKDELAY);
  for (uint8_t i = 0; i < 20; i++) Mouse.move(120, 33);
  delay(CLICKDELAY);  
  Mouse.click(); //выбор 1 эксп
  delay(CLICKDELAY);  
  exphelper();  //----------------------------------------------сбор 
  for (uint8_t i = 0; i < 21; i++) Mouse.move(-127, -85);
  delay(CLICKDELAY);  
  Mouse.click(); //выбор Елань
  delay(CLICKDELAY);

  for (uint8_t i = 0; i < 41; i++) Mouse.move(-127, -127);//--------------------------------------------------------------ЯПОНИЯ
  for (uint8_t i = 0; i < 6; i++) Mouse.move(32, 127);
  delay(EXTENDELAY);
  Mouse.click(); //япония
  delay(CLICKDELAY);
  for (uint8_t i = 0; i < 20; i++) Mouse.move(127, -8);
  delay(CLICKDELAY);  
  Mouse.click(); //выбор 1 эксп
  exphelper();  //----------------------------------------------сбор
  for (uint8_t i = 0; i < 21; i++) Mouse.move(-127, -97);
  delay(CLICKDELAY);  
  Mouse.click(); //выбор кукихи
}

void buttonstateupdate() {  //проверка матрицы кнопок
  //buttonstateprev = buttonstate;
  buttonstate = 0;
  pinMode(c1, OUTPUT);
  digitalWrite(c1, 0);
  if (digitalRead(r1) == 0)
    buttonstate |= 1 << 0;
  if (digitalRead(r2) == 0)
    buttonstate |= 1 << 1;
  if (digitalRead(r3) == 0)
    buttonstate |= 1 << 2;
  if (digitalRead(r4) == 0)
    buttonstate |= 1 << 3;
  pinMode(c1, INPUT);

  pinMode(c2, OUTPUT);
  digitalWrite(c2, 0);
  if (digitalRead(r1) == 0)
    buttonstate |= 1 << 4;
  if (digitalRead(r2) == 0)
    buttonstate |= 1 << 5;
  if (digitalRead(r3) == 0)
    buttonstate |= 1 << 6;
  if (digitalRead(r4) == 0)
    buttonstate |= 1 << 7;
  pinMode(c2, INPUT);

  pinMode(c3, OUTPUT);
  digitalWrite(c3, 0);
  if (digitalRead(r1) == 0)
    buttonstate |= 1 << 8;
  if (digitalRead(r2) == 0)
    buttonstate |= 1 << 9;
  if (digitalRead(r3) == 0)
    buttonstate |= 1 << 10;
  if (digitalRead(r4) == 0)
    buttonstate |= 1 << 11;
  pinMode(c3, INPUT);

  pinMode(c4, OUTPUT);
  digitalWrite(c4, 0);
  if (digitalRead(r1) == 0)
    buttonstate |= 1 << 12;
  if (digitalRead(r2) == 0)
    buttonstate |= 1 << 13;
  if (digitalRead(r3) == 0)
    buttonstate |= 1 << 14;
  if (digitalRead(r4) == 0)
    buttonstate |= 1 << 15;

  pinMode(c4, INPUT);
  // if(buttonstate == buttonstateprev)
  //   buttonstateprev = 0;
  // else{
  //   buttonstateprev = 1;
  // }
}
void macrostatedraw() {  //отрисовка интерфейса
  for (uint8_t i = 0; i < 4; i++)
    for (uint8_t j = 0; j < 4; j++)
      if (macrostate & 1 << (i + j * 4))
        lcd.drawCircle(44 + i * 50, 54 + j * 50, 24, GREEN);
      else {
        //lcd.fillCircle(44 + i * 50, 54 + j * 50, 24, BLACK);
        lcd.drawCircle(44 + i * 50, 54 + j * 50, 24, RED);
      }
      macroupdate = 0;
}
void macro() {  //сами макросы
  macroupdate = macrostate;

  macrostate &= ~(1 << 0);  //                                                    lmb spam 1.1
  if (buttonstate & 1 << 0) {
    Mouse.click(MOUSE_LEFT);
    macrostate |= 1 << 0;
  }

  macrostate &= ~(1 << 1);  //                                                    rmb spam 1.2
  if (buttonstate & 1 << 1) {
    Mouse.click(MOUSE_RIGHT);
    macrostate |= 1 << 1;
  }

  if (buttonstate & 1 << 2) {  //                                                 lmb spam toggle 1.3
    if (!(macrocng & 1 << 2)) {
      if ((macrostate & 1 << 2)) macrostate &= ~(1 << 2);
      else macrostate |= 1 << 2;
      macrocng |= 1 << 2;
    }
  } else macrocng &= ~(1 << 2);
  if (macrostate & 1 << 2) Mouse.click(MOUSE_LEFT);

  if (buttonstate & 1 << 3) {  //                                                 rmb spam toggle 1.4
    if (!(macrocng & 1 << 3)) {
      if ((macrostate & 1 << 3)) macrostate &= ~(1 << 3);
      else macrostate |= 1 << 3;
      macrocng |= 1 << 3;
    }
  } else macrocng &= ~(1 << 3);
  if (macrostate & 1 << 3) Mouse.click(MOUSE_RIGHT);

  if (buttonstate & 1 << 4) {  //                                                 lmb hold toggle 2.1
    if (!(macrocng & 1 << 4)) {
      if ((macrostate & 1 << 4)) macrostate &= ~(1 << 4);
      else macrostate |= 1 << 4;
      macrocng |= 1 << 4;
    }
  } else macrocng &= ~(1 << 4);
  if ((macrostate & 1 << 4)) Mouse.press(MOUSE_LEFT);
  else Mouse.release(MOUSE_LEFT);

  if (buttonstate & 1 << 5) {  //                                                 rmb hold toggle 2.2
    if (!(macrocng & 1 << 5)) {
      if (macrostate & 1 << 5) macrostate &= ~(1 << 5);
      else macrostate |= 1 << 5;
      macrocng |= 1 << 5;
    }
  } else macrocng &= ~(1 << 5);
  if ((macrostate & 1 << 4)) Mouse.press(MOUSE_RIGHT);
  else Mouse.release(MOUSE_RIGHT);

  macrostate &= ~(1 << 6);  //                                                      gi artifact 2.3
  if (buttonstate & 1 << 6) {    
    macrostate |= 1 << 6;
    macroupdate = 1;
    for (uint8_t i = 0; i < 41; i++) Mouse.move(-127, -127);
    for (uint8_t i = 0; i < 35; i++) Mouse.move(127, 58);
    delay(20);
    Mouse.click();  //авто
    delay(20);
    for (uint8_t i = 0; i < 6; i++) Mouse.move(0, 127);
    delay(20);
    Mouse.click();  //вкачать
    delay(20);
    for (uint8_t i = 0; i < 33; i++) Mouse.move(-127, -71);
    delay(20);
    Mouse.click();  //детали
    delay(20);
    Mouse.move(0, 100);
    delay(300);
    Mouse.click();  //улучшить
  }

  macrostate &= ~(1 << 7);  //                                                      gi expeditions 2.4
  if (buttonstate & 1 << 7) {
    macrostate |= 1 << 7;
    macroupdate = 1;
    expeditions12h();
    expeditions20h();
  }

  macrostate &= ~(1 << 8);  //                                                      gi expeditions 3.1
  if (buttonstate & 1 << 8) {
    macrostate |= 1 << 8;
    macroupdate = 1;
    expeditions12h();
  }

  macrostate &= ~(1 << 9);  //                                                      gi expeditions 3.2
  if (buttonstate & 1 << 9) {
    macrostate |= 1 << 9;
    macroupdate = 1;
    expeditions20h();
  }

  macrostate &= ~(1 << 14);  //                                                      powershell 4.3
  if (buttonstate & 1 << 14) {
    delay(10);
    Keyboard.press(KEY_LEFT_GUI);
    delay(10);
    Keyboard.write('r');
    delay(10);
    Keyboard.release(KEY_LEFT_GUI);
    delay(100);
    Keyboard.print("powershell");
    delay(100);
    Keyboard.write(KEY_RETURN);
    macrostate |= 1 << 14;
  }

  macrostate &= ~(1 << 15);//                                                        OFF OFF OFF OFF 4.4
  if (buttonstate & 1 << 15) {
    macrostate = 1 << 15;
  }

  if (macrostate != macroupdate) macroupdate = 1;
}

void setup() {
  Keyboard.begin();
  Mouse.begin();
  lcd.init(SCR_WD, SCR_HT);
  lcd.fillScreen(BLACK);
  lcd.setCursor(22, 0);
  lcd.setTextColor(WHITE);
  lcd.setTextSize(3);
  lcd.print("MACRO STATE");
  pinMode(r1, INPUT_PULLUP);
  pinMode(r2, INPUT_PULLUP);
  pinMode(r3, INPUT_PULLUP);
  pinMode(r4, INPUT_PULLUP);
  macrostatedraw();
}
void loop() {
  buttonstateupdate();                //опрос кнопок
  macro();                            //сами макросы
  delay(DELAYOFFSET);                 //задержечка
}
void yield() {
  if (macroupdate) macrostatedraw();  //обновить экранчик
}
