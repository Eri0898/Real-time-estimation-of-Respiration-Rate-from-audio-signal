#include <Ewma.h>
#include <EwmaT.h>
#include <SD.h>
#include <SPI.h>

#define SD_ChipSelectPin 10
#define LOWPASS_ANALOG_PIN_AMT 6

File myFile;

float lowpass_prev_out[LOWPASS_ANALOG_PIN_AMT], 
      lowpass_cur_out[LOWPASS_ANALOG_PIN_AMT];
int   lowpass_input[LOWPASS_ANALOG_PIN_AMT];

int r[60];
int p[25];
int count = 0;
float u;

int adcsample_and_lowpass(int pin, int sample_rate, int samples, float alpha, char use_previous) { 
  float one_minus_alpha = 1.0-alpha;
  int micro_delay=max(100, (1000000/sample_rate) - 160);
  if (!use_previous) { 
    lowpass_input[pin] = analogRead(pin);
    lowpass_prev_out[pin]=lowpass_input[pin]; 
  } 
  int i;
  for (i=samples;i>0;i--) {
    delayMicroseconds(micro_delay);
    lowpass_input[pin] = analogRead(pin);
    lowpass_cur_out[pin] = alpha*lowpass_input[pin] + one_minus_alpha*lowpass_prev_out[pin];
    lowpass_prev_out[pin]=lowpass_cur_out[pin];
  }
  return lowpass_cur_out[pin];
}

void setup(){
  Serial.begin(9600);
  pinMode(A0, INPUT);
}

void loop(){
  if(Serial.available()){
    if(Serial.read()=='r'){
      for(int i=0;i<23;i++){
        u = (float)analogRead(0)*5/1024;
        p[i]  = 2*(0.1041*p[i]+0.8959*u);
        delay(400);
        //Serial.println(p[i]);
        }

        for(int j=2;j<=23;j++){
          if(p[j]>p[j+1] & p[j]>p[j-1] & p[j]!=p[j-1]){
            count++;
          }
      }
      
      if(count<=2){
        Serial.println("Long breaths");
        count=0;
        while(Serial.available()){
        Serial.println("Recording...");
        for(int i=0;i<60;i++){
        r[i]  = adcsample_and_lowpass(0, 10, 600, 0.9, true);
        Serial.println(r[i]);
      }
        for(int j=2;j<=60;j++){
          if(r[j]>r[j+1] & r[j]>r[j-1] & r[j]>r[j+2] & r[j]>r[j-2]){
            count++;
          }
        }
        Serial.print("Respiration Rate:");
        Serial.println(count);
        memset(r, 0, sizeof(r));
      }
      }
      
      else if(count>2){
        Serial.println("Normal breaths");
        count=0;
        while(Serial.available()){
          Serial.println("Recording...");
          for(int i=0;i<60;i++){
            r[i]  = adcsample_and_lowpass(0, 10, 600, 0.9, true);
            Serial.println(r[i]);
          }
          for(int j=1;j<=60;j++){
            if(r[j]>r[j+1] & r[j]>r[j-1]){
              count++;
            }
          }
        Serial.print("Respiration Rate:");
        Serial.println(count);
        memset(r, 0, sizeof(r));
      }
      }
    }
  }
}
