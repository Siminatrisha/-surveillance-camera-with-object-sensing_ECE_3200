#include <SoftwareSerial.h>
SoftwareSerial BT_Serial(2, 3); 


#define enA 10//Enable1 L298 Pin enA 
#define in1 9 //Motor1  L298 Pin in1 
#define in2 8 //Motor1  L298 Pin in1 
#define in3 7 //Motor2  L298 Pin in1 
#define in4 6 //Motor2  L298 Pin in1 
#define enB 5 //Enable2 L298 Pin enB 



#define echo A2   
#define trigger A3


long distance;
int distance_F = 30;
int set = 20;

int Speed = 90;
   
int bt_ir_data; 

int mode=0;

void setup(){ 

pinMode(echo, INPUT); 
pinMode(trigger, OUTPUT); 
pinMode(enA, OUTPUT); 
pinMode(in1, OUTPUT); 
pinMode(in2, OUTPUT); 
pinMode(in3, OUTPUT); 
pinMode(in4, OUTPUT); 
pinMode(enB, OUTPUT); 



Serial.begin(9600); 
BT_Serial.begin(9600); 


}


void loop(){  

if(BT_Serial.available() > 0){  
bt_ir_data = BT_Serial.read(); 
Serial.println(bt_ir_data);     
if(bt_ir_data > 20){Speed = bt_ir_data;}      
}



     if(bt_ir_data == 8){mode=0; Stop();}   
else if(bt_ir_data == 9){mode=1; Speed=130;}
else if(bt_ir_data ==10){mode=2; Speed=255;} 
if(mode==0){     
     if(bt_ir_data == 1){forword(); } 
else if(bt_ir_data == 2){backword();} 
else if(bt_ir_data == 3){turnLeft();}
else if(bt_ir_data == 4){turnRight();} 
else if(bt_ir_data == 5){Stop(); }      
else if(bt_ir_data == 6){turnLeft();  delay(400);  bt_ir_data = 5;}
else if(bt_ir_data == 7){turnRight(); delay(400);  bt_ir_data = 5;}
}



if(mode==2){         
 distance_F = Ultrasonic_read();
 Serial.print("S=");Serial.println(distance_F);
  if (distance_F < set)
  {
        Stop();
  }
  
 else
  {
         forword();
 
  }
  
}

delay(10);
}


long Ultrasonic_read(){
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  distance = pulseIn (echo, HIGH);
  return distance / 29 / 2;
}

void forword(){  
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
digitalWrite(in3, LOW);   
digitalWrite(in4, HIGH); 

 
}

void backword(){ 

digitalWrite(in1, LOW);  
digitalWrite(in2, HIGH); 
digitalWrite(in3, HIGH); 
digitalWrite(in4, LOW); 
 
}

void turnRight(){ 

digitalWrite(in1, HIGH); 
digitalWrite(in2, LOW); 
digitalWrite(in3, HIGH);  
digitalWrite(in4, LOW); 

  
}
void turnLeft(){


digitalWrite(in1, LOW); 
digitalWrite(in2, HIGH); 
digitalWrite(in3, LOW);  
digitalWrite(in4, HIGH); 

}
void Stop(){

digitalWrite(in1, LOW); 
digitalWrite(in2, LOW);
digitalWrite(in3, LOW);
digitalWrite(in4, LOW);

}