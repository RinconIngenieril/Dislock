#include "Keyboard.h"
#include <EEPROM.h>

//Constant
#define velocidadSonido 340 //Units m/s

//IO pins
int button = 4;
int LED = 10;
int echo = 3;
int trigger = 2;

//Variables
float distance;
int max_distance = 60;
bool armed = true;
bool enable = false;
int count = 0;
int set_count = 0;
int led_pwm = 0;

//Functions prototipes 
void doYourMagic();
void LED_control(bool pwm, int count, int t, int LED);
float getDistance(int trigger, int echo);
int calibration(int trigger, int echo);


void setup() {
  pinMode(button, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(echo,INPUT);      //Pin echo como salida
  pinMode(trigger,OUTPUT);  //Pin de disparo como entrada
  
  Keyboard.begin();
  Serial.begin(9600);       //Inicializar puerto serie

  enable = EEPROM.read(0);
  max_distance = EEPROM.read(1);
}

void loop() {

  distance = getDistance(trigger, echo);

  //Distance detection
  if(distance > max_distance and armed == true){
    count++;
  } else if(distance < max_distance and armed == false){
    count++;
  } else if (distance < 10) { 
    set_count++;
  } else if (set_count < 10){
    count = 0;
    set_count = 0;
  }

  //Timers triggers
  if (count > 10 and armed == true){              //Lock Trigger
    doYourMagic();
    count = 0;    
    armed = false;  
  } else if (count > 10 and armed == false){      //Rearme the system
    count = 0;
    armed = true;
  } else if (set_count > 10) {                    //Enter congif mode
    digitalWrite(LED, LOW);
    delay(5000);
    // If distance is < 10 cm less than 5 seconds, enter calibration mode
    // else enter enable/disble mode 
    if (getDistance(trigger, echo) > 10){
      //Repeat until no error is found
      do {
        LED_control(false, 4, 200, LED);
        max_distance = 20 + calibration(trigger, echo);
      } while(max_distance > 255);
      EEPROM.write(1, max_distance);
    } else {
      LED_control(false, 2, 200, LED);
      enable = !enable;
      EEPROM.write(0, enable);
      delay(1000);
      LED_control(false, 2, 200, LED);
    }      
    set_count = 0;
  }  
  
  //Serial debug
  /*Serial.print(distance);
  Serial.print(" ");
  Serial.print(count);
  Serial.print(" ");
  Serial.print(armed);
  Serial.print(" ");
  Serial.print(set_count);
  Serial.print(" ");
  Serial.print(max_distance);
  Serial.print(" ");
  Serial.println(enable);*/

  //Enable and armed status LED
  if (enable == true){
    if (armed == true) 
      analogWrite(LED, 50);
    else
      digitalWrite(LED, LOW);
    delay(100);
  }
  else {
    LED_control(true, 1, 100, LED);
  }    

}

//Send the CTRL-ALT-L keyboard shortcut for Ubuntu
void doYourMagic(){
   // CTRL-ALT-l:
   if (enable == true) {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.write('l'); 
    Keyboard.releaseAll();
    delay(100);
   }
}

//Make the LED blink "count" times or write a PWM
void LED_control(bool pwm, int count, int t, int LED){

  if (pwm == true){
    if (led_pwm == 50)
      led_pwm = 0;
    analogWrite(LED, led_pwm);
    delay(t);
    led_pwm++;
  } else {
    for (int i = 0; i < count; i++) {
      digitalWrite(LED, HIGH);
      delay(t);
      digitalWrite(LED, LOW);
      delay(t);
    }
  }
  
}

//Read and calc the distance in the old fashioned way
float getDistance(int trigger, int echo){

  float echoTime;
  float distance;
  
  digitalWrite(trigger,LOW);
  delayMicroseconds(2);
  digitalWrite(trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);
  echoTime = pulseIn(echo, HIGH);
  echoTime = echoTime/1000000.0;
  distance = echoTime * velocidadSonido;
  distance = distance * 100;
  distance = distance /2;

  return distance;
}

//Calibration process. Get the distance 20 times and do the arithmetic mean
int calibration(int trigger, int echo){

  int calibration_distance = 0;
  do{
    for ( int i = 0; i < 20; i++){
      delay(100);
      int distance = getDistance(trigger, echo);
      if ( i == 0)
        calibration_distance = distance;
      else
        calibration_distance = (calibration_distance + distance)/2;
    }
  } while(calibration_distance > 150);

  return calibration_distance;
  
}
