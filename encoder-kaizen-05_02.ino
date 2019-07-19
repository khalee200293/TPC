
#define  encoderPinA  2 
#define  encoderPinB  3
#define  relay  7 
volatile  int encoderPos = 0;  
int lastReportedPos = 1; 
static boolean rotating=false;
boolean A_set = false;             
boolean B_set = false;
 int newposition;
 int button = 8;
 int oldposition=0;
 long newtime;
 long oldtime=0;
 int vantoc = 0;
 int ganvantoc = 0;
 int ganxung = 0;
 int sovong = 0;
   void setup() {
        pinMode(encoderPinA, INPUT_PULLUP);      
        pinMode(encoderPinB, INPUT_PULLUP);
        pinMode(relay, OUTPUT);  
        pinMode(button, INPUT);
        attachInterrupt(0, doEncoderA, CHANGE);     
        attachInterrupt(1, doEncoderB, CHANGE);
        Serial.begin(9600);  
     }
void loop() {
   delay(200);
   rotating = true;
   newtime=millis();
   newposition=encoderPos;
   detachInterrupt(0);
   detachInterrupt(1);
   vantoc = (newposition-oldposition)*60/1000;
   //Serial.println(vantoc);
    Sosanh();
    oldposition=newposition;
    oldtime=newtime;
    attachInterrupt(0, doEncoderA, CHANGE);
    attachInterrupt(1, doEncoderB, CHANGE); 
}
void doEncoderA(){
  if ( rotating ) delay (1);
  if( digitalRead(encoderPinA) != A_set ) { 

    A_set = !A_set;
    if ( A_set && !B_set )
      encoderPos += 1;
      ganxung += 1;
      sovong=encoderPos/1000;
      if (ganxung == 42){ganxung=0;}
      //if (ganxung == 200){ganxung=0;}
      rotating = false;
      }
  }
void doEncoderB(){
  if ( rotating ) delay (1);
  if( digitalRead(encoderPinB) != B_set ) {
    B_set = !B_set;
    if( B_set && !A_set )
      encoderPos -= 1;
      rotating = false;
  }
}
void Sosanh()
{   
         if(digitalRead(button))
           { //delay(300);
                  if(vantoc ==0)
                    {  delay(300);
                       if(vantoc ==0)
                       {digitalWrite(relay, LOW);}
                    }
                  else{digitalWrite(relay,HIGH);}
           
           }

    else { 
      digitalWrite(relay,HIGH);
  }
 }
