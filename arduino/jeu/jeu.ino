int led0 = 5;
int led1 = 6;
int led2 = 7;

int led;
int previousLed = 0;

int sensor0 = 2;
int sensor1 = 1;
int sensor2 = 0;

int value0;
int value1;
int value2;

void setup()
{
  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  Serial.begin(9600);

}

void loop()
{
  value0 = analogRead(sensor0);
  value1 = analogRead(sensor1);
  value2 = analogRead(sensor2);

  int tirage = random(20, 70);

  for(int i = 0; i<tirage; i++){
    led = random (3);
    if(led==previousLed){
      led=random(3);
    }
    previousLed=led;

    if(led==0){
      digitalWrite(led0,HIGH);
    }
    else if(led==1){
      digitalWrite(led1,HIGH);
    }  
    else if(led==2){
      digitalWrite(led2,HIGH);
    }   

    delay(200);

    digitalWrite(led0,LOW);  
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    delay(100);
  }
  
  delay(30000);
}



