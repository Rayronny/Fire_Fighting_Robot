/*
Connections to be made 05/04/23
Left Motors : Motor 1 d25 and d26
              Motor 2 d27 and d14
Right Motors : Motor 1 d18 and d19 
               Motor 2 d21 and d22 
Tatenda Bako,Lawrence Takaendesa,Emmanuel Damba, Raymond Nyakudanga 
*/
#include <WiFi.h>
#include <WiFiClient.h>  // to be able to connect to connect to hotspot
#include <WebServer.h>   // to make a server in arduino
#include <HTTPClient.h>  // to be abkle to make https requests to and from client (POST, GET, PUT, DELETE)
#include <DabbleESP32.h>

#define RightFrontFWD 18
#define RightFrontBWD 19
#define RightBackFWD 21
#define RightBackBWD 22

#define LeftFrontFWD 25
#define LeftFrontBWD 26
#define LeftBackFWD 27
#define LeftBackBWD 14

void setup() {
  pinMode(RightFrontFWD, OUTPUT);
  pinMode(RightFrontBWD, OUTPUT);
  pinMode(RightBackFWD, OUTPUT);
  pinMode(RightBackBWD, OUTPUT);
  pinMode(LeftFrontFWD, OUTPUT);
  pinMode(LeftFrontBWD, OUTPUT);
  pinMode(LeftBackFWD, OUTPUT);
  pinMode(LeftBackBWD, OUTPUT);
  // put your setup code here, to run once:
  Serial.begin(115200);      // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin("Fire-Fighter-ESP32");       //set bluetooth name of your device
}

void loop() {
  Dabble.processInput();//this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  Serial.print("KeyPressed: ");
  if (GamePad.isUpPressed())
  {
    Serial.print("Up");
    moveForward();
  } else if (GamePad.isDownPressed())
  {
    Serial.print("Down");
    moveBackward();
  } else if (GamePad.isLeftPressed())
  {
    Serial.print("Left");
    rotateLeft();
  } else if (GamePad.isRightPressed())
  {
    Serial.print("Right");
    rotateRight();
  } else if (GamePad.isSquarePressed())
  {
    Serial.print("Square");
    moveSidewaysRight();
  } else if (GamePad.isCirclePressed())
  {
    Serial.print("Circle");
    moveSidewaysLeft();
  } else if (GamePad.isCrossPressed())
  {
    Serial.print("Cross");
    moveRightForward();
  } else if (GamePad.isTrianglePressed())
  {
    Serial.print("Triangle");
    moveLeftForward();
  } else
  {
    stopMoving();
  }

  /*if (GamePad.isStartPressed())
    {
    Serial.print("Start");
    }

    if (GamePad.isSelectPressed())
    {
    Serial.print("Select");
    } */
  Serial.print('\t');

  int a = GamePad.getAngle();
  Serial.print("Angle: ");
  Serial.print(a);
  Serial.print('\t');
  int b = GamePad.getRadius();
  Serial.print("Radius: ");
  Serial.print(b);
  Serial.print('\t');
  float c = GamePad.getXaxisData();
  Serial.print("x_axis: ");
  Serial.print(c);
  Serial.print('\t');
  float d = GamePad.getYaxisData();
  Serial.print("y_axis: ");
  Serial.println(d);
  Serial.println();
}

void moveForward() {
  digitalWrite(RightFrontFWD, HIGH);
  digitalWrite(RightFrontBWD, LOW);
  digitalWrite(RightBackFWD, HIGH);
  digitalWrite(RightBackBWD, LOW);

  digitalWrite(LeftFrontFWD, HIGH);
  digitalWrite(LeftFrontBWD, LOW);
  digitalWrite(LeftBackFWD, HIGH);
  digitalWrite(LeftBackBWD, LOW);
}

void moveBackward() {
  digitalWrite(RightFrontFWD, LOW);
  digitalWrite(RightFrontBWD, HIGH);
  digitalWrite(RightBackFWD, LOW);
  digitalWrite(RightBackBWD, HIGH);

  digitalWrite(LeftFrontFWD, LOW);
  digitalWrite(LeftFrontBWD, HIGH);
  digitalWrite(LeftBackFWD, LOW);
  digitalWrite(LeftBackBWD, HIGH);
}

void rotateRight() {
  digitalWrite(RightFrontFWD, LOW);
  digitalWrite(RightFrontBWD, HIGH);
  digitalWrite(RightBackFWD, LOW);
  digitalWrite(RightBackBWD, HIGH);

  digitalWrite(LeftFrontFWD, HIGH);
  digitalWrite(LeftFrontBWD, LOW);
  digitalWrite(LeftBackFWD, HIGH);
  digitalWrite(LeftBackBWD, LOW);
}

void rotateLeft() {
  digitalWrite(RightFrontFWD, HIGH);
  digitalWrite(RightFrontBWD, LOW);
  digitalWrite(RightBackFWD, HIGH);
  digitalWrite(RightBackBWD, LOW);

  digitalWrite(LeftFrontFWD, LOW);
  digitalWrite(LeftFrontBWD, HIGH);
  digitalWrite(LeftBackFWD, LOW);
  digitalWrite(LeftBackBWD, HIGH);
}

void moveSidewaysRight() {
  digitalWrite(RightFrontFWD, LOW);
  digitalWrite(RightFrontBWD, HIGH);
  digitalWrite(RightBackFWD, HIGH);
  digitalWrite(RightBackBWD, LOW);

  digitalWrite(LeftFrontFWD, HIGH);
  digitalWrite(LeftFrontBWD, LOW);
  digitalWrite(LeftBackFWD, LOW);
  digitalWrite(LeftBackBWD, HIGH);
}

void moveSidewaysLeft() {
  digitalWrite(RightFrontFWD, HIGH);
  digitalWrite(RightFrontBWD, LOW);
  digitalWrite(RightBackFWD, LOW);
  digitalWrite(RightBackBWD, HIGH);

  digitalWrite(LeftFrontFWD, LOW);
  digitalWrite(LeftFrontBWD, HIGH);
  digitalWrite(LeftBackFWD, HIGH);
  digitalWrite(LeftBackBWD, LOW);
}

void moveRightForward() {
  digitalWrite(RightFrontFWD, LOW);
  digitalWrite(RightFrontBWD, LOW);
  digitalWrite(RightBackFWD, HIGH);
  digitalWrite(RightBackBWD, LOW);

  digitalWrite(LeftFrontFWD, HIGH);
  digitalWrite(LeftFrontBWD, LOW);
  digitalWrite(LeftBackFWD, LOW);
  digitalWrite(LeftBackBWD, LOW);
}

void moveLeftForward() {
  digitalWrite(RightFrontFWD, HIGH);
  digitalWrite(RightFrontBWD, LOW);
  digitalWrite(RightBackFWD, LOW);
  digitalWrite(RightBackBWD, LOW);

  digitalWrite(LeftFrontFWD, LOW);
  digitalWrite(LeftFrontBWD, LOW);
  digitalWrite(LeftBackFWD, HIGH);
  digitalWrite(LeftBackBWD, LOW);
}

void stopMoving() {
  digitalWrite(RightFrontFWD, LOW);
  digitalWrite(RightFrontBWD, LOW);
  digitalWrite(RightBackFWD, LOW);
  digitalWrite(RightBackBWD, LOW);

  digitalWrite(LeftFrontFWD, LOW);
  digitalWrite(LeftFrontBWD, LOW);
  digitalWrite(LeftBackFWD, LOW);
  digitalWrite(LeftBackBWD, LOW);
}
  