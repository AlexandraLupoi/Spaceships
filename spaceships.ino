#include <EEPROM.h>
#include <LedControl.h>
#include <LiquidCrystal.h>

#define SW_PIN 2
#define X_PIN A0
#define Y_PIN A1

#define V0_PIN 9

#define VAL_MIN 400
#define VAL_MAX 600

LedControl lc = LedControl(12, 11, 10, 1);

LiquidCrystal lcd(3, 4, 5, 6, 7, 8);

int valoareX, valoareY, anteriorX, anteriorY, pozitieX, pozitieY;
int linie, coloana, obstacol, arma;
int nivel = 0, viata = 3, scor = 0, sfarsit = 0;

const int minMatrice = 0, maxMatrice = 7, dimMatrice = 8, nrObstacole = 15;

bool matrice[nrObstacole][dimMatrice];

bool nivel1[nrObstacole][dimMatrice] = { {1, 0, 1, 0, 1, 0, 1, 0},
                                         {0, 1, 0, 1, 0, 1, 0, 1},
                                         {1, 0, 0, 1, 0, 0, 1, 0},
                                         {0, 1, 0, 0, 1, 0, 0, 1},
                                         {1, 1, 0, 1, 0, 1, 0, 1},
                                         {0, 1, 1, 0, 1, 1, 0, 0},
                                         {1, 0, 1, 0, 0, 1, 0, 1},
                                         {0, 1, 0, 1, 1, 0, 1, 0},
                                         {1, 1, 0, 1, 1, 0, 1, 1},
                                         {1, 0, 1, 0, 1, 0, 1, 1},
                                         {0, 1, 1, 0, 1, 0, 1, 1},
                                         {1, 1, 0, 0, 1, 0, 1, 1},
                                         {1, 1, 0, 0, 1, 1, 0, 1},
                                         {1, 0, 0, 1, 1, 0, 0, 1},
                                         {1, 1, 0, 0, 0, 1, 1, 0}  };

bool nivel2[nrObstacole][dimMatrice] = { {1, 1, 0, 1, 0, 1, 1, 1},
                                         {0, 1, 1, 1, 0, 0, 1, 1},
                                         {1, 0, 1, 1, 0, 1, 1, 1},
                                         {0, 1, 1, 0, 0, 1, 1, 0},
                                         {1, 1, 0, 1, 1, 0, 1, 1},
                                         {1, 0, 1, 1, 1, 1, 0, 1},
                                         {0, 1, 1, 1, 0, 1, 1, 0},
                                         {1, 0, 1, 0, 1, 1, 1, 1},
                                         {0, 1, 1, 1, 1, 0, 1, 1},
                                         {1, 1, 1, 0, 1, 1, 1, 1},
                                         {1, 0, 0, 1, 1, 1, 1, 0},
                                         {1, 0, 1, 1, 1, 1, 0, 1},
                                         {1, 1, 1, 1, 0, 1, 1, 1},
                                         {1, 1, 1, 0, 0, 1, 1, 1},
                                         {0, 0, 1, 1, 0, 1, 1, 1}  };

bool nivel3[nrObstacole][dimMatrice] = { {1, 1, 1, 0, 1, 1, 1, 1},
                                         {1, 0, 1, 1, 1, 1, 0, 1},
                                         {1, 1, 0, 1, 1, 1, 1, 0},
                                         {1, 1, 1, 1, 0, 0, 1, 1},
                                         {1, 0, 1, 1, 1, 1, 1, 0},
                                         {1, 1, 1, 0, 0, 0, 1, 1},
                                         {1, 0, 1, 1, 0, 1, 1, 1},
                                         {0, 0, 1, 1, 1, 1, 1, 0},
                                         {1, 1, 1, 1, 1, 0, 0, 1},
                                         {1, 1, 1, 0, 0, 1, 1, 1},
                                         {0, 0, 1, 1, 1, 1, 1, 1},
                                         {1, 1, 0, 0, 1, 1, 1, 1},
                                         {0, 1, 0, 1, 1, 1, 1, 1},
                                         {1, 1, 1, 1, 0, 1, 1, 0},
                                         {1, 1, 1, 1, 1, 0, 0, 0}  };

void setariJoc() {
  nivel = 0;
  viata = 3;
  scor = 0;
  sfarsit = 0;
}

void nivelJoc() {
  pozitieX = 3;
  pozitieY = 6;
  for (int i = 0; i < nrObstacole; i++)
    for (int j = 0; j < dimMatrice; j++)
    {
      if (nivel == 1)
        matrice[i][j] = nivel1[i][j];
      if (nivel == 2)
        matrice[i][j] = nivel2[i][j];
      if (nivel == 3)
        matrice[i][j] = nivel3[i][j];
    }
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("LEVEL");
  lcd.setCursor(8, 1);
  lcd.print((String)nivel);
  delay(1000);
  for (obstacol = 0; obstacol < nrObstacole; obstacol++)
  {
    for (linie = 0; linie < dimMatrice; linie++)
    {
      nava();
      if (viata == 0)
      {
        lcd.clear();
        lcd.setCursor(6, 0);
        lcd.print("GAME");
        lcd.setCursor(6, 1);
        lcd.print("OVER");
        delay(1000);
        lcd.clear();
        nivel = 4;
        sfarsit = 1;
        break;
      }
    }
    if (sfarsit == 1)
      break;
  }
  if (sfarsit == 0)
  {
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print((String)"LEVEL " + nivel);
    lcd.setCursor(3, 1);
    lcd.print("FINISHED:)");
    delay(1000);
    lcd.clear();
  }
}

void nava() {
  valoareX = analogRead(X_PIN);
  valoareY = analogRead(Y_PIN);
  if (valoareY < VAL_MIN)
  {
    anteriorY = pozitieY;
    if (pozitieY > minMatrice)
      pozitieY--;
  }
  if (valoareY > VAL_MAX)
  {
    anteriorY = pozitieY;
    if (pozitieY + 1 < maxMatrice)
      pozitieY++;
  }
  if (valoareX < VAL_MIN)
  {
    anteriorX = pozitieX;
    if (pozitieX > minMatrice)
      pozitieX--;
  }
  if (valoareX > VAL_MAX)
  {
    anteriorX = pozitieX;
    if (pozitieX < maxMatrice)
      pozitieX++;
  }
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print((String)"LIVES : " + viata);
  lcd.setCursor(4, 1);
  lcd.print((String)"SCORE : " + scor);
  for (coloana = 0; coloana < dimMatrice; coloana++)
    lc.setLed(0, linie, coloana, matrice[obstacol][coloana]);
  lc.setLed(0, pozitieY, pozitieX, true);
  lc.setLed(0, pozitieY + 1, pozitieX, true);
  if (digitalRead(SW_PIN) == 0)
  {
    arma = pozitieY - 1;
    while (arma >= 0)
    {
      lc.setLed(0, arma, pozitieX, true);
      delay(50);
      lc.setLed(0, arma, pozitieX, false);
      if (matrice[obstacol][pozitieX] == 1 && arma == linie)
      {
        int stanga = 0;
        int dreapta = 0;
        int nr = 1;
        int i = pozitieX - 1;
        int j = pozitieX + 1;
        matrice[obstacol][pozitieX] = 0;
        while (stanga != -1)
        {
          if (matrice[obstacol][i] == 1)
          {
            matrice[obstacol][i] = 0;
            lc.setLed(0, arma, i, false);
            i--;
            nr++;
          }
          if (matrice[obstacol][i] == 0 || i < minMatrice)
            stanga = -1;
        }
        while (dreapta != -1)
        {
          if (matrice[obstacol][j] == 1)
          {
            matrice[obstacol][j] = 0;
            lc.setLed(0, arma, j, false);
            j++;
            nr++;
          }
          if (matrice[obstacol][j] == 0 || j > maxMatrice)
            dreapta = -1;
        }
        scor = scor + nr;
        arma = -1;
      }
      arma--;
    }
  }
  if (matrice[obstacol][pozitieX] == 1 && pozitieY == linie)
    viata--;
  delay((4 - nivel) * 100);
  for (coloana = 0; coloana < dimMatrice; coloana++)
    lc.setLed(0, linie, coloana, false);
  lc.setLed(0, pozitieY, pozitieX, false);
  lc.setLed(0, pozitieY + 1, pozitieX, false);
}

void scorJoc() {
  if (scor > EEPROM.read(0))
    EEPROM.update(0, scor);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print((String)"YOUR SCORE: " + scor);
  lcd.setCursor(1, 1);
  lcd.print((String)"HIGH SCORE: " + EEPROM.read(0));
  delay(2000);
  lcd.clear();
}

void restartJoc() {
  lcd.setCursor(3, 0);
  lcd.print("TRY AGAIN?");
  lcd.setCursor(2, 1);
  lcd.print("<--YES NO-->");
  valoareX = analogRead(X_PIN);
  if (valoareX < VAL_MIN)
    setariJoc();
  if (valoareX > VAL_MAX)
  {
    lcd.noDisplay();
    lc.shutdown(0, true);
  }
}

void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0, 2);
  lc.clearDisplay(0);
  lcd.begin(16, 2);
  lcd.clear();
  pinMode(V0_PIN, OUTPUT);
  analogWrite(V0_PIN, 90);
  pinMode(SW_PIN, INPUT_PULLUP);
}

void loop() {
  if (nivel == 0)
  {
    lcd.clear();
    lcd.setCursor(6, 0);
    lcd.print("START");
    lcd.setCursor(6, 1);
    lcd.print("GAME!");
    delay(1000);
    if (digitalRead(SW_PIN) == 0)
      nivel = 1;
  }
  if (viata != 0 && nivel > 0  && nivel < 4)
  {
    nivelJoc();
    nivel++;
  }
  if (viata != 0 && nivel == 4)
  {
    scorJoc();
    viata = 0;
  }
  restartJoc();
}
