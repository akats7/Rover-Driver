#include <NewPing.h>  
#define NUM_SENSORS 3 
#define PINA 8
#define PINB 9
#define INTERRUPT 0  // pin 2
#define DIRECTIONA 2 // A is left 
#define MOTORA 3
#define DIRECTIONB 12 // B is Right 
#define MOTORB 11
#define TIME_FORWARDS 3000
#define TIME_BACKWARDS 3000
#define TIME_TURN 1100
#define TIME_PWM 1100
volatile int rotaryCount = 0;

void setup() {
  delay(100);
  Serial.begin(9600);
  pinMode(A4,INPUT);
  pinMode (MOTORA, OUTPUT);
  pinMode (DIRECTIONA, OUTPUT);
  pinMode (MOTORB, OUTPUT);
  pinMode (DIRECTIONB, OUTPUT);
  delay(5000);
  while(
    analogRead(18) < 1000){
    delay(100);
    Serial.println(analogRead(A4));
  }
 FORWARDS();
 delay(300);
 LEFT90();
}


int x,y,z,q,b=0;

byte phase;
unsigned long start;
int time_to_go;

void FORWARDS () {
 Serial.println("FORWARD"); 
  digitalWrite (DIRECTIONA, 1);
  digitalWrite (DIRECTIONB, 1);
 analogWrite(MOTORA,150);//Serial.println("Forwards");
  analogWrite(MOTORB,150);
}

void BACKWARDS () {
  analogWrite(MOTORA,150);
  analogWrite(MOTORA,150);
  digitalWrite (DIRECTIONA, 0);
  digitalWrite (DIRECTIONB, 0);
}

void RIGHT90 () {
  Serial.println("RIGHT TURN");
    analogWrite(MOTORA, 175);
    analogWrite(MOTORB, 175);
    digitalWrite (DIRECTIONA, 1);
    digitalWrite (DIRECTIONB, 0);
    delay (1200);
    STOP();
}

void LEFT90 ()
{
  
  Serial.println("LEFT TURN");
  analogWrite(MOTORA,175);
  analogWrite(MOTORB,175);
  digitalWrite(DIRECTIONA, 0);
  digitalWrite(DIRECTIONB,1);
  delay (1200); 
  STOP();
}

void STOP () { 
  analogWrite (MOTORA, 0);
  analogWrite (MOTORB, 0);

}
void COAST() {
  analogWrite( MOTORA,50);
  analogWrite(MOTORB,50);}
  
void LEFTPWM () { 
  Serial.println( "LEFT PWM");
  digitalWrite(DIRECTIONA,1);
  digitalWrite(DIRECTIONB,1);
  analogWrite (MOTORA, 100);
  analogWrite (MOTORB, 250);
}

void RIGHTPWM ()
{Serial.println("Right PWM");
  
  analogWrite (MOTORA, 250);
  analogWrite (MOTORB, 100);
  digitalWrite(DIRECTIONA,1);
  digitalWrite(DIRECTIONB,1);
 time_to_go = TIME_PWM;
 STOP();
 delay (300);
}

//void RIGHTPWM ()
//{
//  digitalWrite (DIRECTIONA, 1);
//  digitalWrite (DIRECTIONB, 0);
//  time_to_go = TIME_PWM;
//  STOP();
//  delay (300);
//}

void RIGHTPT2 () {
  Serial.println("RIGHT TURN");
  analogWrite(MOTORA, 150);
  analogWrite(MOTORB, 150) ;
  digitalWrite (DIRECTIONA, 1);
  digitalWrite (DIRECTIONB, 0);
  delay (1700);
  STOP();
}

void LEFTPT2 () {
  Serial.println("LEFT TURN");
  analogWrite(MOTORA,150);
  analogWrite(MOTORB,150);
  digitalWrite(DIRECTIONA, 0);
  digitalWrite(DIRECTIONB,1);
  delay (1700);STOP();
  
}

NewPing sonar[NUM_SENSORS]={
  NewPing (10,9,200),
  NewPing(8,7,200),
  NewPing(6,5,200)};

void loop() {
 start = millis ();
 if (analogRead(A4) > 800){
 // check current drain
 while (millis () - start < time_to_go) {
   if (analogRead (0) > 325)  // > 1.46 amps
     break;    
   }
  if (millis() < 90000){
  x=sonar[0].ping_cm();
  _delay_ms(10);
  y=sonar[1].ping_cm();
  _delay_ms(10);
  z=sonar[2].ping_cm();
  _delay_ms(10); 

Serial.println(x);
Serial.println(y);
Serial.println(z);

//Serial.println(sonar[Sensor].ping_in());
//_delay_ms(500);
if(x!= 0 && y!=0 && z!=0){
  if (x <= 17){ //Serial.println(Right turn)
  
  RIGHT90();
  
}
else if (x > 20 && y > 22 && z>22){ 

  LEFT90();
  FORWARDS();
  delay(1070);
}
else if (x > 17 && (((y == 15)&&(z ==15))||(y>17 && z<20))){ //Serial.println(Forwards);
  FORWARDS();
}

//else if (x > 5) && (y < 6) && (y > 2) //(y <6z)  && (y>2) { //Serial.println(LeftPWM)
else if( (x>17) && (y<=22) && (y>=15) )
{
LEFTPWM();
}
 
//else if (x > 5 && (y <= 2){ //Seriy<=2al.println(RIGHT PWM)
else if ( (x>17) && (y<15)){
RIGHTPWM();
}
else { 
//
FORWARDS();
delay(100);
STOP(); //Serial.println(STOP);
//FORWARDS();
}
}
else if((x=0)&&(y!=0) && (z!=0)){
  while(x=0) {
    BACKWARDS();
  }
  //delay(400);
}
else{
  
 RIGHTPWM();
 delay(100);
 STOP();

}
}
else if (millis() >= 90000){


NewPing sonar[4]={
  NewPing (10,9,200),
  NewPing(8,7,200),
  NewPing(6,5,200),
NewPing(13,4,200)};


x=sonar[0].ping_cm();
delay(10);
y=sonar[1].ping_cm();
delay(10);
z=sonar[2].ping_cm();
delay(10);
q=sonar[3].ping_cm();
delay(200);
b=b+1;
Serial.println(x);

Serial.println(y);

Serial.println(z);

Serial.println(q);

if ( (x<50 || q<50))
{
  if (b % 3 == 0){
  RIGHTPT2();
  
  }
  else{ LEFTPT2();
  
  }}
  else if (x==0 || q==0) {
    FORWARDS();
  }
  else {
    FORWARDS();
  }
}
else{
}}
else{
  STOP();
}
}
// 
// put your main code here, to run repeatedly:
//while(1){ 
//  
//  
//x=sonar.ping_in();
//Serial.println(x);
//  NewPing sonar(10,9,200);
//y=sonar.ping_in();
//if(x > 1){
// 
//  digitalWrite(i-5, HIGH);
//}
//  else { digitalWrite(i-5,LOW);
//  }
//            
//_delay_ms(200);
//}
//i=7;
 





//
//void loop() {
//  // put your main code here, to run repeatedly:
//while(1){ 
//  for (i=7;i<14;i+2){
//  NewPing sonar(i+1,i,200);
//x=sonar.ping_in();
//Serial.println(x);
//if(x > 1){
// 
//  digitalWrite(i-5, HIGH);
//}
//  else { digitalWrite(i-5,LOW);
//  }
//            
//_delay_ms(200);
//}
//i=7;
//} 
//
//}


