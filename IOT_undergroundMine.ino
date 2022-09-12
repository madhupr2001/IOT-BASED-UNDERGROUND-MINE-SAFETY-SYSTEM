#include <Adafruit_MLX90614.h>
#include <MQ2.h>
#include <Wire.h> 
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

int temp_reading =0;
int Analog_Input = A0;
int lpg, co, smoke;
const int buzzer = 12;
const int red_led = 13;
MQ2 mq2(Analog_Input);



void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  mq2.begin();
  //Serial.println("Adafruit MLX90614 test");

 if (!mlx.begin()) {
    Serial.println("Error connecting to MLX sensor. Check wiring.");
   
  }
}

void loop() {
    Serial.print("Ambient = "); 
    Serial.print(mlx.readAmbientTempC());
    temp_reading = mlx.readAmbientTempC();
    Serial.print("*C\tObject = "); 
    Serial.print(temp_reading ); 

    /*if(temp_reading < 30)
        {
        digitalWrite(red_led,HIGH);
        digitalWrite(buzzer,HIGH);
        
        }

      if(temp_reading > 35)
      {
      digitalWrite(red_led,LOW);
      digitalWrite(buzzer,LOW);
      }*/
    Serial.println("*C");
    Serial.print("Ambient = "); 
    temp_reading = mlx.readAmbientTempF();
    Serial.print(temp_reading);
    Serial.print("*F\tObject = "); 
    Serial.print(mlx.readObjectTempF()); Serial.println("*F");
    
    

  Serial.println();
  delay(500);


  float* values= mq2.read(true); //set it false if you don't want to print the values in the Serial
  //lpg = values[0];
  lpg = mq2.readLPG();
  //co = values[1];
  co = mq2.readCO();
  //smoke = values[2];
  smoke = mq2.readSmoke();
 
  Serial.print("LPG :");
  Serial.println(lpg);
  Serial.print("CO :");
  Serial.println(co);
  Serial.print("SMOKE:");
  Serial.print(smoke);
  Serial.println(" PPM");
  delay(1000);


  if((temp_reading < 30) || (lpg>20) || (co > 25) || (smoke > 100))
        {
        digitalWrite(13,HIGH);
        digitalWrite(12,HIGH);
        
        }

      if(temp_reading > 30 || (lpg < 20) || (co < 25) || (smoke <100))
      {
      digitalWrite(13,LOW);
      digitalWrite(12,LOW);
      
      }
}
