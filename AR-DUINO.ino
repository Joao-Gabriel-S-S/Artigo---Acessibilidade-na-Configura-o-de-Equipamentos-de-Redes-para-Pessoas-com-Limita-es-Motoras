#include <Keyboard.h>
#include <Mouse.h>

// Definindo os pinos dos botões
const int buttonPins[] = {2, 3, 4, 5, 6, 7, 9};
const int numButtons = sizeof(buttonPins) / sizeof(int);

// Estado anterior dos botões
int lastButtonState[numButtons] = {0};

const int xAxis = A0;         // sensor analogico para o eixo X
const int yAxis = A1;         // sensor analogico para o eixo Y

int range = 4;               // output range do movimento de X ou Y
int responseDelay = 2;        // dalay do mouse em ms
int threshold = range / 4;    // limiar de repouso
int center = range / 2;       // valor de repouso
int minima[] = {1023, 1023};  // atual minima analogRead para {x, y}
int maxima[] = {0, 0};        // atual maxima analogRead para {x, y}
int axis[] = {xAxis, yAxis};  // numeros pin para {x, y}
int mouseReading[2];          // leitura final de {x, y}

void setup() {
  // Inicializando Mouse e Keyboard
  Mouse.begin();
  Keyboard.begin();

  // Configurando os pinos dos botões como INPUT
  for (int i = 0; i < numButtons; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
}

void loop() {

  // ler e dar escala para os dois eixos
  int xReading = readAxis(0);
  int yReading = readAxis(1);

  // mover o mouse
  Mouse.move(xReading, yReading, 0);
  delay(responseDelay);

  // Verificando se o estado do botão na porta 2 mudou
  if (digitalRead(buttonPins[0]) != lastButtonState[0]) {
    lastButtonState[0] = !lastButtonState[0];
    if (lastButtonState[0] == LOW) {
      Mouse.move(0, 0, -1);  // Scroll para baixo
      delay(300);
    }
  }

  // Verificando se o estado do botão na porta 3 mudou
  if (digitalRead(buttonPins[1]) != lastButtonState[1]) {
    lastButtonState[1] = !lastButtonState[1];
    if (lastButtonState[1] == LOW) {
      Keyboard.println("senha roteador");
      delay(300);
    }
  }

  // Verificando se o estado do botão na porta 4 mudou
  if (digitalRead(buttonPins[2]) != lastButtonState[2]) {
    lastButtonState[2] = !lastButtonState[2];
    if (lastButtonState[2] == LOW) {
      Mouse.click(MOUSE_LEFT);
      delay(300);
    }
  }

  // Verificando se o estado do botão na porta 5 mudou
  if (digitalRead(buttonPins[3]) != lastButtonState[3]) {
    lastButtonState[3] = !lastButtonState[3];
    if (lastButtonState[3] == LOW) {
      Keyboard.println("nome wifi");
      delay(300);
    }
  }

  // Verificando se o estado do botão na porta 6 mudou
  if (digitalRead(buttonPins[4]) != lastButtonState[4]) {
    lastButtonState[4] = !lastButtonState[4];
    if (lastButtonState[4] == LOW) {
      Mouse.click(MOUSE_RIGHT);
      delay(300);
    }
  }

  if (digitalRead(buttonPins[5]) != lastButtonState[5]) {
    lastButtonState[5] = !lastButtonState[5];
    if (lastButtonState[5] == LOW) {
      delay(500); //meio segundo para o computador processar
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press('r');
      Keyboard.releaseAll();
      delay(1000); //um segundo para o computador processar
      Keyboard.println("CMD");
      delay(1500); //outro um segundo e meio para o computador processar
      Keyboard.print("start https");
      Keyboard.write(63); // digita "/"
      Keyboard.println("192.168.3.1");
      delay(300);
    }
  }

  // Verificando se o estado do botão na porta 9 mudou
  if (digitalRead(buttonPins[6]) != lastButtonState[6]) {
    lastButtonState[6] = !lastButtonState[6];
    if (lastButtonState[6] == LOW) {
      Keyboard.println("senha wifi");
      delay(300);
    }
  }
}

// https://www.arduino.cc/reference/tr/language/functions/usb/mouse/mousemove/
int readAxis(int axisNumber) {
  int distance = 0; // distance from center of the output range

  // read the analog input:
  int reading = analogRead(axis[axisNumber]);

  // of the current reading exceeds the max or min for this axis,
  // reset the max or min:
  if (reading < minima[axisNumber]) {
    minima[axisNumber] = reading;
  }
  if (reading > maxima[axisNumber]) {
    maxima[axisNumber] = reading;
  }

  // map the reading from the analog input range to the output range:
  reading = map(reading, minima[axisNumber], maxima[axisNumber], 0, range);

  // if the output reading is outside from the
  // rest position threshold,  use it:
  if (abs(reading - center) > threshold) {
    distance = (reading - center);
  }

  // return the distance for this axis:
  return distance;
}