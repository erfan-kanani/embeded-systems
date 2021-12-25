/*
Code for Arduino Line Follower Robot 
PORT 10 is input for Left Motor 
PORT 9 is input for Right Motor
We use 5 IR sensors to track black line 
*/

int left_motor = 10;
int right_motor = 9;
void setup() {
  Serial.begin(9600);
  pinMode(left_motor, OUTPUT);
  pinMode(right_motor, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  analogWrite(left_motor, 255);
  analogWrite(right_motor, 255);
}

void loop() {
  int high = 255;
  int low = 240;
  int very_low = 80;

  int a0 = digitalRead(A0);
  int a1 = digitalRead(A1);
  int a2 = digitalRead(A2);
  int a3 = digitalRead(A3);
  int a4 = digitalRead(A4);

  if(a0 == LOW && a1 == LOW && a3 == LOW && a4 == LOW){
    analogWrite(right_motor, high);
    analogWrite(left_motor, low);
  }
  else if(a0 == LOW && a1 == LOW){
    analogWrite(right_motor, high);
    analogWrite(left_motor, 0);
  }
  else if(a3 == LOW && a4 == LOW){
    analogWrite(right_motor, 0);
    analogWrite(left_motor, high);
  }
  else if(a2 == LOW){
    analogWrite(left_motor, high);
    analogWrite(right_motor, high);
  }
  else if(a0 == LOW){
    analogWrite(left_motor, very_low);
    analogWrite(right_motor, high);
  }
  else if(a1 == LOW){
    analogWrite(left_motor, low);
    analogWrite(right_motor, high);
  }
  else if(a3 == LOW){
    analogWrite(left_motor, high);
    analogWrite(right_motor, low);
  }
  else if(a4 == LOW){
    analogWrite(left_motor, high);
    analogWrite(right_motor, very_low);
  }
}