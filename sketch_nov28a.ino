#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#include <TM1637.h>
#include "LEDControl.h"
#include "RTClib.h"
#include <SD.h>
#include <SPI.h>
#include <TMRpcm.h>
#define SDPin 10
#define AudioPin 9
TMRpcm tmrpcm;
RTC_DS3231 rtc;
//Sensor
#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04
long durationJ; // variable for the durationJ of sound wave travel
int distance; // variable for the distance measurement

#define disCM 50
//NumDisplay
int CLK = 6;
int DIO = 5;
TM1637 tm(CLK,DIO);

//Buzzer
int buzzer = 7 ;


void setup() {
 tmrpcm.speakerPin = AudioPin;
  Serial.begin(9600);
  if(!SD.begin(SDPin)){
    Serial.println("SD Fail");
    return;
  }
  Serial.println("SD Succeed");
  File root, song;
  root = SD.open("/");
  Serial.println(SD.exists("MARIAH~1.WAV"));
//  printDirectory(root,0);
  tmrpcm.setVolume(6);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  
  setupLEDS(colorPin, NUMPIXELS);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT]

  tm.init();
  tm.set(7);

  pinMode (buzzer, OUTPUT) ;
}
void loop() {
 DateTime now = rtc.now();
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationJ = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = durationJ * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // displayNumber(distance);
        tm.point(1);
    tm.display(3, now.minute() % 10);
    tm.display(2, now.minute() / 10 % 10);
    tm.display(1, now.hour() % 10);
    tm.display(0, now.hour() / 10 % 10);
   if(now.hour()>=8 && now.hour()<23)
    color(distance);
}
void color(int x){
   DateTime now = rtc.now();

   
    
  if(x<150 && x!=0){
      if(!tmrpcm.isPlaying())
    tmrpcm.play("MARIAH~1.WAV");
      }
       for(int j=0; j<NUMPIXELS; j++)
        pixels.setPixelColor(j, pixels.Color(0, 0, 0));  
        pixels.show();
}

void displayNumber(int num){   
    tm.display(3, num % 10);   
    tm.display(2, num / 10 % 10);   
    tm.display(1, num / 100 % 10);   
    tm.display(0, num / 1000 % 10);
}
