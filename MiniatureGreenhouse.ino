#include <dht11.h>

const int H_out = 3;
const int fan_out = 5;
const int bulb_out = 6;
#define DHT11_PIN 7

dht11 DHT11;

// Defining pinouts for various in/outs
const int Temp_in = A1;
// const int Moist_in = A2;

// Defining cut-off points
const float T_high = 50.0;
const float T_low = 36.0;
const float M_high = 60;
const float M_low = 50; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(H_out, OUTPUT);
  pinMode(fan_out, OUTPUT);
  pinMode(bulb_out, OUTPUT);

}

void loop() {
  
  delay(2000);
  // put your main code here, to run repeatedly:

  // Measring and Printing Temp reading
  float temp_adc_val;
  float temp_val;
  temp_adc_val = analogRead(Temp_in);        /* Read Temperature */
  temp_val = (temp_adc_val * 500)/1023;       /* Convert adc value to equivalent voltage */
  Serial.print("Temperature = ");
  Serial.print(temp_val);
  Serial.print(" Degree Celsius\n");
  delay(1000); 

  float chk = DHT11.read(DHT11_PIN);
  Serial.print("DHT Temperature = ");
  Serial.println(DHT11.temperature);
  Serial.print("DHT Humidity = ");
  Serial.println(DHT11.humidity);


  // Switch ON the fan when temp goes above a Temp
  if (temp_val > T_high)
  {
    digitalWrite(fan_out, HIGH);
  }
  // Switch OFF the fan when temp goes above a Temp
  else if (temp_val < T_high - 5)
  {
    digitalWrite(fan_out, LOW);
  }

  if (temp_val < T_low )
  {
    digitalWrite(bulb_out, HIGH);
  }
  else if (temp_val > T_low + 5 )
  {
    digitalWrite(bulb_out, LOW);
  }


  // Measuring and printing Moisture reading.
  if (DHT11.humidity > M_high)
  {
     digitalWrite(H_out, LOW);
     digitalWrite(fan_out, HIGH);
  }
  else
  {
    digitalWrite(H_out, HIGH);
    digitalWrite(fan_out, LOW);
  }



}
