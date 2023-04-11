// assign meaningful names to those pins that will be used
const int pinL_Sensor = A5;      //pin A5
const int pinM_Sensor = A2;      //pin A2
const int pinR_Sensor = A3;      //pin A3
const int pinB_Sensor = A0;      //pin A0
const int pinL_PWM = 9;          //pin D9
const int pinR_PWM = 11;         //pin D11
const int pinL_DIR = 10;         //pin D10
const int pinR_DIR = 12;         //pin D12

//define variables to be used in script
int leftSensor = 1;
int lastLeftSensor = 1;

int midSensor  = 1;

int rightSensor = 1;
int lastRightSensor = 1;

int bumpSensor = 1;
int lastBumpSensor = 1;

int stage = 0;
int splitCount = 0;

int wheelSpeed = 200;

bool split;
bool prevsplit;
bool starting = true;

// the setup function runs once when you press reset or power the board

void setup ()
{
  // define pins as input and output
  pinMode(pinL_Sensor, INPUT);
  pinMode(pinM_Sensor, INPUT);
  pinMode(pinR_Sensor, INPUT);
  pinMode(pinB_Sensor, INPUT);
  
  pinMode(pinL_DIR, OUTPUT);
  pinMode(pinR_DIR, OUTPUT);
  
  pinMode(pinL_PWM, OUTPUT);
  pinMode(pinR_PWM, OUTPUT);
  
  // initialize output pins
  digitalWrite(pinL_DIR, HIGH);   //forward direction    
  digitalWrite(pinR_DIR, HIGH);   //forward direction
  analogWrite(pinL_PWM, 0);    //forward speed 
  analogWrite(pinR_PWM, 0);    //forward speed 
}

// the loop function runs over and over again forever

void loop()
{
  leftSensor = digitalRead(pinL_Sensor);
  midSensor = digitalRead(pinM_Sensor);
  rightSensor = digitalRead(pinR_Sensor);
  bumpSensor = digitalRead(pinB_Sensor);
  

  if(bumpSensor!=lastBumpSensor && bumpSensor == 0)
  {
    stage += 1;
    delay(200);
  }
  lastBumpSensor = bumpSensor;
  
  if(stage==0)//stop
  {
        analogWrite(pinL_PWM, 0);
        analogWrite(pinR_PWM, 0);
        digitalWrite(pinL_DIR, LOW);
        digitalWrite(pinR_DIR, LOW); 
  }
  else if(stage==1)//forward
  {
    if(!leftSensor && !rightSensor)
    {
        split = true;
        if(!midSensor && starting)
        {
          analogWrite(pinL_PWM, wheelSpeed);
          analogWrite(pinR_PWM, wheelSpeed);
          digitalWrite(pinL_DIR, HIGH);
          digitalWrite(pinR_DIR, HIGH);
          delay(200); 
          starting = false;     
        }
        if(splitCount == 1 || splitCount==2)
        {
          analogWrite(pinL_PWM, wheelSpeed-50);
          analogWrite(pinR_PWM, wheelSpeed);
          digitalWrite(pinL_DIR, LOW);
          digitalWrite(pinR_DIR, HIGH);
          delay(200); 
        }
        else if(splitCount==3)
        {
          analogWrite(pinL_PWM, wheelSpeed);
          analogWrite(pinR_PWM, wheelSpeed-50);
          digitalWrite(pinL_DIR, HIGH);
          digitalWrite(pinR_DIR, LOW); 
          delay(200);
        }
    }
       
    if(!leftSensor && rightSensor)
    {
        analogWrite(pinL_PWM, wheelSpeed);
        analogWrite(pinR_PWM, wheelSpeed);
        digitalWrite(pinL_DIR, LOW);
        digitalWrite(pinR_DIR, HIGH);
        split = false;
        
    }
    
    if(leftSensor && !rightSensor)
    {
        analogWrite(pinL_PWM, wheelSpeed);
        analogWrite(pinR_PWM, wheelSpeed);
        digitalWrite(pinL_DIR, HIGH);
        digitalWrite(pinR_DIR, LOW);
        split = false;
        
    }
    
    if(leftSensor && rightSensor)
    {
        analogWrite(pinL_PWM, wheelSpeed);
        analogWrite(pinR_PWM, wheelSpeed);
        digitalWrite(pinL_DIR, HIGH);
        digitalWrite(pinR_DIR, HIGH);
        split = false;
    }
    if (split == false && prevsplit == true){
        splitCount += 1;
    }
    prevsplit = split;
    
  }
  //====================================================================================
  else if(stage==2)//backward
  {
    for(int i=0;i<1;i++)
    {
      analogWrite(pinL_PWM, 200);
      analogWrite(pinR_PWM, 200);
      digitalWrite(pinL_DIR, LOW);
      digitalWrite(pinR_DIR, LOW);
      delay(1100);
    }
    
    analogWrite(pinL_PWM, 0);
    analogWrite(pinR_PWM, 0);
    digitalWrite(pinL_DIR, LOW);
    digitalWrite(pinR_DIR, LOW);
    delay(50000);
  }
}
