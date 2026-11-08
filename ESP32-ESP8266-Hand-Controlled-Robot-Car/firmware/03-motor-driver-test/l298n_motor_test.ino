#define IN1 D1
#define IN2 D2
#define IN3 D5
#define IN4 D6

void stopMotors(){ digitalWrite(IN1,LOW); digitalWrite(IN2,LOW); digitalWrite(IN3,LOW); digitalWrite(IN4,LOW); }
void forward(){ digitalWrite(IN1,LOW); digitalWrite(IN2,HIGH); digitalWrite(IN3,LOW); digitalWrite(IN4,HIGH); }
void reverse(){ digitalWrite(IN1,HIGH); digitalWrite(IN2,LOW); digitalWrite(IN3,HIGH); digitalWrite(IN4,LOW); }

void setup(){
  pinMode(IN1,OUTPUT); pinMode(IN2,OUTPUT); pinMode(IN3,OUTPUT); pinMode(IN4,OUTPUT);
  stopMotors();
}

void loop(){
  forward(); delay(2000);
  stopMotors(); delay(1000);
  reverse(); delay(2000);
  stopMotors(); delay(2000);
}
