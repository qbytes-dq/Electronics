/*

  state = !state;
*/

const byte motorStep = 3;
const byte motorDir  = 4;
const byte onOff  = 5;

const byte interruptPinIR = 2;


/**
 * Mitsumi 35PS-9
 * ==============
 * 24V 
 * 517mA max
 * 970 pps out
 * 740 pps in
 * --------------
 * 7.5 degree per step
 * Full -  48 steps full revolution (360 degree)
 * 1/2  -  96 steps
 * 1/4  - 192 steps
 * 1/8  - 384 steps
 * 1/16 - 768 steps --->  (this is what I'm using)
 */

const double stepDegree = 7.5;
const double microStep = 16; // 1/16

const double gear1 = 23;
const double gear2 = 28;
const double gearRation = gear2 / gear1;

const double gear1StepsPerRev = (360 / stepDegree) * microStep;
const double gear1_steps360 = 360.0 / stepDegree;
const double gear2_steps360 = gear1_steps360  * gearRation;
const double gear2StepsPerRev = gear1StepsPerRev * gearRation;

double stepSizeGear2 = 360.0 / gear2StepsPerRev;

volatile byte state = LOW;
unsigned long loopCnt = 9999999;

volatile boolean activeRun = false;


// the setup function runs once when you press reset or power the board
void setup() {
  // open the serial port at 115200 bps:
  Serial.begin(115200);
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(motorStep, OUTPUT);
  pinMode(motorDir, OUTPUT);
  pinMode(onOff, OUTPUT);

  pinMode (interruptPinIR, INPUT);
  //attachInterrupt(digitalPinToInterrupt(interruptPinIR), cntDetectIR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPinIR), debounceInterrupt, CHANGE);
  
  state = LOW;

  printInfo();
  }

void printInfo(){
  Serial.println("Coil Winder");
  Serial.println("=============================");

  Serial.println(stepSizeGear2*1000);

  Serial.println(gearRation);
  Serial.println(gear1StepsPerRev);
  Serial.println(gear2StepsPerRev);
  Serial.println(stepSizeGear2);  

  Serial.println("-----------------------------");
}

// the loop function runs over and over again forever
void loop() {
  if (activeRun){
    loopCnt++;

    doStep();

//    Serial.print(loopCnt);
//    Serial.print (" _ ");
//    Serial.println((double)loopCnt * stepSizeGear2);
    
    if (loopCnt > gear2StepsPerRev){
      activeRun = false;
      Serial.print("arF:");   
      Serial.print ("Gear2Steps: ");
      Serial.println(gear2StepsPerRev);  
    }
  }
}



long debouncing_time = 1; //Debouncing Time in Milliseconds
volatile unsigned long last_millis;
volatile int b=0;

void debounceInterrupt() {
  if((long)(millis() - last_millis) >= debouncing_time * 1000) {
    Interrupt();
    cntDetectIR();
    last_millis = millis(); //micros();
  }else{
    Serial.println ("early");
    return;
  }

  Serial.print ("Debounce Time: ");
  Serial.println (debouncing_time * 1000);
    
  Serial.print ("last_micros Time: ");
  Serial.println (last_millis);
  
}


void Interrupt() {
  b++;
  Serial.print ("B: ");
  Serial.println (b);
}


void cntDetectIR() {
  state = digitalRead(interruptPinIR);
  digitalWrite(onOff,state);

  if (state){      
    Serial.println("Rise: ");
    return;
  }else{
    Serial.println("Fall: ");
  }

  if (activeRun){
    return;
  }
 
  if (loopCnt >= gear2StepsPerRev){
    loopCnt = 0;
    activeRun = true;
    Serial.print("arT:");   
  }    

  Serial.print(state);   
  Serial.print(":");   
  Serial.println(activeRun);  
}

void doStep(){
  digitalWrite(motorStep, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1);                       // wait for a second
  digitalWrite(motorStep, LOW);    // turn the LED off by making the voltage LOW
  //delay(1);                       // wait for a second 
}
