#include <MsTimer2.h>
int ledpin = 7;
int btRight = 2;
int btPause = 3;
int btLeft = 4;

int input1 = 9;
int input2 = 10;



int RightWay = 10000;

String NewStatus = "";


void setup() {
  Serial.begin(9600);
  pinMode(ledpin, OUTPUT);
  pinMode(btRight, INPUT);
  pinMode(input1, OUTPUT);
  pinMode(input2, OUTPUT);

  MsTimer2::set(100, CheckWay);        // 中断设置函数，每 100ms 进入一次中断
  MsTimer2::start();                //开始计时


}

void CheckWay() {

  if (NewStatus == "Left") {
    digitalWrite(input1, HIGH);
    digitalWrite(input2, LOW);
    RightWay = RightWay + 100;
  }

  if (NewStatus == "Right") {
    digitalWrite(input1, LOW);
    digitalWrite(input2, HIGH);
    RightWay = RightWay - 100;
  }


  if (NewStatus == "Pause") {
    digitalWrite(input1, LOW);
    digitalWrite(input2, LOW);
  }


  //=======
  if (RightWay >= 10000) {
    RightWay = 10000;
    MovePause();
  }

  if (RightWay <= 0) {
    RightWay = 0;
    MovePause();
  }
  //=======

  //Serial.println(RightWay);


  if (NewStatus == "Left" || NewStatus == "Right") {
    digitalWrite(ledpin, HIGH);
  }
  else {
    digitalWrite(ledpin, LOW);
  }


}

void loop() {

  

  if ((digitalRead(btRight) == HIGH && digitalRead(btPause) == HIGH) || (digitalRead(btRight) == HIGH && digitalRead(btLeft) == HIGH) || (digitalRead(btLeft) == HIGH && digitalRead(btPause) == HIGH) || (digitalRead(btLeft) == HIGH && digitalRead(btPause) == HIGH && digitalRead(btRight) == HIGH)) {
    Serial.println("Skip");
    return;
  } else {


    /*
        if (digitalRead(btRight) == HIGH || digitalRead(btPause) == HIGH || digitalRead(btLeft) == HIGH) {
          digitalWrite(ledpin, HIGH);
        }
        else {
          digitalWrite(ledpin, LOW);
        }
    */




    if (digitalRead(btRight) == HIGH)
    {

      delay(10);
      if (digitalRead(btRight) == HIGH) {
        //Serial.println("Right");
        //MoveRight();
        NewStatus = "Right";
      }


    }


    //=================

    if (digitalRead(btPause) == HIGH) //读取触摸传感器的状态值
    {

      delay(10);
      if (digitalRead(btPause) == HIGH) {
        //Serial.println("Pause");
        //MovePause();
        NewStatus = "Pause";
      }


    }



    //=================

    if (digitalRead(btLeft) == HIGH) //读取触摸传感器的状态值
    {

      delay(10);
      if (digitalRead(btLeft) == HIGH) {
        //Serial.println("Left");
        //MoveLeft();
        NewStatus = "Left";
      }

    }

    //====================

    int value = analogRead(A0);//雨水传感器

    if (value < 1000 )
    {
      NewStatus = "Right";

    }





  }


}



/*void MoveLeft() {
  digitalWrite(input1, HIGH);
  digitalWrite(input2, LOW);
  }


  void MoveRight() {
  digitalWrite(input1, LOW);
  digitalWrite(input2, HIGH);

  }*/

void MovePause() {
  digitalWrite(input1, LOW);
  digitalWrite(input2, LOW);
  NewStatus = "Pause";

}

