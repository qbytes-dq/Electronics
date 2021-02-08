
  // ------------------------------------------------------
  // open the serial port at 115200 bps:
  // ------------------------------------------------------




  // ------------------------------------------------------
  // initialize Stepper motor.
  // ------------------------------------------------------
/*  state = !state;  */

const byte motorStep = 3;
const byte motorDir  = 4;
const byte onOff  = 5;

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

  // ------------------------------------------------------
  // iterupt for rotory encoder
  // ------------------------------------------------------
const byte interruptRotory = 2;

  // ------------------------------------------------------
  // iterupt for IR winder loop counter 
  // ------------------------------------------------------
const byte interruptPinIR = 2;
  
  // ------------------------------------------------------
  // LCD setup
  // ------------------------------------------------------
// SDA is pin A4
// SCL is pin A5
#include <LiquidCrystal_I2C.h> //from newliquidcrystal library
LiquidCrystal_I2C lcd(0x27, 20, 4);  // Set the LCD I2C address



// SETUP function runs once when you press reset or power the board
void setup() {
  // ------------------------------------------------------
  // open the serial port at 115200 bps:
  // ------------------------------------------------------
  Serial.begin(115200);
  printInfo();
  
  // ------------------------------------------------------
  // initialize Stepper motor.
  // ------------------------------------------------------
  pinMode(motorStep, OUTPUT);
  pinMode(motorDir, OUTPUT);
  pinMode(onOff, OUTPUT);

  digitalWrite(motorDir, HIGH); 

  // ------------------------------------------------------
  // iterupt for rotory encoder
  // ------------------------------------------------------
//  pinMode (interruptPinIR, INPUT);
//  attachInterrupt(digitalPinToInterrupt(interruptPinIR), debounceInterrupt, CHANGE);
  
  state = LOW;

  // ------------------------------------------------------
  // iterupt for Loop counter 
  // ------------------------------------------------------
  pinMode (interruptPinIR, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPinIR), debounceInterrupt, CHANGE);



  // ------------------------------------------------------
  // LCD setup
  // ------------------------------------------------------
  lcd.init();
  lcd.backlight();

  delay(2000);  
  lcd.clear();  

  lcd.setCursor(0, 0);
  lcd.print("Coil Winder");
  lcd.setCursor(0, 1);
  lcd.print("abc                 ");
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

// LOOP function runs over and over again forever
void loop() {

  doStep();
      
  if (activeRun){
    loopCnt++;

    //doStep();

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
