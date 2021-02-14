  // ------------------------------------------------------
  // Set serial port baud
  // ------------------------------------------------------
  unsigned long baudRate = 115200;

  // ------------------------------------------------------
  // initialize winder gear.
  // ------------------------------------------------------
    const byte motorEnable =  A0;
    const byte motor1A =  A1;
    const byte motor2A =  A2;

  // ------------------------------------------------------
  // initialize Stepper motor.
  // ------------------------------------------------------
  /*
  // https://www.amazon.com/gp/product/B076KDFSGT/ref=ppx_yo_dt_b_asin_title_o01_s03?ie=UTF8&psc=1
  // https://lastminuteengineers.com/28byj48-stepper-motor-arduino-tutorial/
  // https://lastminuteengineers.com/28byj48-stepper-motor-arduino-tutorial/
  // https://drive.google.com/drive/folders/1f9AJ35WYjUg4OXALgNlhoYUSVtt6FYw9
  */

  // ==================================================
  // 28BYJ-48 Gear Reduction Ratio
  double motorGearRatios = (32.0/9.0) * (22.0/11.0) * (26.0/9.0) * (31.0/10.0);
  double motorStepDegree  = (11.25 / motorGearRatios );  
  double motorStepsPerRev = 32 * motorGearRatios;
  // Stride Angle ： 5.625° x ~1/64 datasheet is wrong
  // Stride Angle ： 11.25° x ~1/64 website above is correct

  // ==================================================
  double printedGearRatios = (28.0/22.0)* (22.0/22.0) *(22.0/20.0);

  // ==================================================
  double postGearRatios = motorGearRatios * printedGearRatios;
  double postStepDegree  = (11.25 / postGearRatios );  
  double postStepsPerRev = (360.0 / postStepDegree );
  
  // Cir
  #define PI 3.1415926535897932384626433832795 // Overkill.....
  //#define PI 3.14
  double shuttleCircumference = 184 * PI;
  double postCircumference = 22.5 * PI;
  
  enum motion {CCW, CW, STOP};
  void doStep(motion dir);
  
  int stepPOS = 0;
  int stepCount = 0;
  const byte D09 =  9; // Pin 09
  const byte D10 = 10; // Pin 10
  const byte D11 = 11; // Pin 11
  const byte D12 = 12; // Pin 12

// ============================================================
// ============================================================
// ============================================================
 
  // ------------------------------------------------------
  // iterupt for IR winder loop counter 
  // ------------------------------------------------------
  const byte interruptPinIR = 2; // pin 2, Pin D2 = INT0
  volatile unsigned long irCount = 0;
  
  // ------------------------------------------------------
  // interrupt for rotory encoder
  // ------------------------------------------------------
  const byte interruptRotoryPin = 3; // pin 3, Pin D3 = INT1
  const byte directionPin = 4;       // pin 4, Pin D4
  volatile byte direction1 = LOW;
  volatile int rotoryCount = 0;
  volatile double tempRotoryCount = 0.0;
  
  const byte rotorySwitch = 13;  // pin 13, Pin D13

  // ------------------------------------------------------
  // LCD setup
  // ------------------------------------------------------
  // SDA is pin A4
  // SCL is pin A5
  #include <LiquidCrystal_I2C.h> //from newliquidcrystal library
  LiquidCrystal_I2C lcd(0x27, 20, 2);  // Set the LCD I2C address

void printDouble(double number, byte precision){
  precision++; // Need an extra byte
  // Make room for your floating point number, however you plan to format it.
  char floatBuffer[precision];
  
  // Make room for entire print line, however long you plan to make it.
  char printBuffer[precision];

  dtostrf(number, precision, precision, floatBuffer);
  sprintf(printBuffer, "%s", floatBuffer);
  Serial.print(printBuffer);
}

void lcdDouble(double number, byte precision){
  // Make room for your floating point number, however you plan to format it.
  char floatBuffer[precision + 1];
  
  // Make room for entire print line, however long you plan
  // to make it.
  char printBuffer[precision + 1];

  dtostrf(number, precision, precision, floatBuffer);
  sprintf(printBuffer, "%smm ", floatBuffer);

  lcd.print(printBuffer);
}

/* other print double options:
//---------------------------------------------------------------
  float x = -1.234567890123;
  byte precision = 9;  // Number of digits after the decimal point
  
  // Make room for your floating point number, however you
  // plan to format it.
  char floatBuffer[20];
  
  // Make room for entire print line, however long you plan
  // to make it.
  char printBuffer[80];
  
  // Bottom line: The size of floatBuffer must be at least
  // precision+4.  The "width" field in the call do
  // dtostrf should be at least precision plus 3 and at most
  // the size of floatBuffer minus 1
  //
  dtostrf(x, precision+3, precision, floatBuffer);
  
  // You could just print the raw value.  (You might
  // have other Serial.print() statements to give it some
  // user-friendly context.)
  Serial.println(floatBuffer);
  
  
  // Or you could use sprintf to create an entire line in a
  // different buffer.  Then you could use Serial.print
  // or LiquidCrystal::print, or whatever, to emit
  // the whole enchilada in one statement.
  sprintf(printBuffer, "With %%.%df precision, x = %s", precision, floatBuffer);
  Serial.println(printBuffer);
*/

void setup() {
 
  // ------------------------------------------------------
  // open the serial port
  // ------------------------------------------------------
  Serial.begin(baudRate);

  Serial.println("\n\n\n\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
  Serial.println("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
  Serial.println("Toroid winding using:");
  Serial.println("Stepper 28BYJ-48 Gear Reduction with ULN2003 driver");
  Serial.println("\n=====");
  Serial.println("Motor:");
  Serial.println("-----");

  Serial.print  ("motorGearRatios: ");
  printDouble(motorGearRatios , 5);
  Serial.println("");

  Serial.print  ("motorStepsPerRev: ");
  Serial.println(motorStepsPerRev);

  Serial.print  ("motorStepDegree: ");
  printDouble(motorStepDegree , 5);
  Serial.println("");

  Serial.println("=====");
  Serial.println("Printed Gear:");
  Serial.println("-----");
  Serial.print  ("printedGearRatios: ");  
  printDouble(printedGearRatios , 5);
  Serial.println("");

  Serial.println("=====");
  Serial.println("Post:");
  Serial.println("-----");

  Serial.print  ("postGearRatios : ");
  printDouble(postGearRatios , 5);
  Serial.println("");

  Serial.print  ("postStepDegree : ");
  printDouble(postStepDegree , 5);
  Serial.println("");

  Serial.print  ("postStepsPerRev: ");
  Serial.println(postStepsPerRev);
  Serial.println("");

  Serial.println("\n=====");
  Serial.println("Shuttle: ");
  Serial.println("-----");
  Serial.println(shuttleCircumference);
  
  // ------------------------------------------------------
  // initialize winder gear.
  // ------------------------------------------------------
  pinMode(motorEnable, OUTPUT);
  pinMode(motor1A, OUTPUT);
  pinMode(motor2A, OUTPUT);
      
  // ------------------------------------------------------
  // initialize Stepper motor.
  // ------------------------------------------------------
  pinMode(D09, OUTPUT);
  pinMode(D10, OUTPUT);
  pinMode(D11, OUTPUT);
  pinMode(D12, OUTPUT);
  
  // ------------------------------------------------------
  // interrupt for Loop counter 
  // ------------------------------------------------------
  pinMode (interruptPinIR, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPinIR), pinIRInterrupt, FALLING);
  
  // ------------------------------------------------------
  // interrupt for rotory encoder
  // ------------------------------------------------------
  pinMode (interruptRotoryPin, INPUT);
  pinMode (directionPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptRotoryPin), interruptRotory, RISING);

  pinMode (rotorySwitch, INPUT);  
  
  // ------------------------------------------------------
  // LCD setup
  // ------------------------------------------------------
  lcd.init();
  lcd.backlight();
  
  lcd.clear();  
  
  lcd.setCursor(0, 0);
  lcd.print("ToolboxAid.com");

  lcd.setCursor(0, 1);
  lcd.print("Toroid Winder v1");

  delay(3000);   
}


boolean fullPower = false;

void doStep(motion dir){
  if (dir == motion::CCW){
    stepPOS++;
    if (stepPOS >= 4)
      stepPOS = 0;
  }else if (dir == motion::CW){
    stepPOS--;
    if (stepPOS < 0){
      stepPOS = 3;
    }
  } else {//Disable steppers to Stop
    digitalWrite(D09, LOW); 
    digitalWrite(D10, LOW); 
    digitalWrite(D11, LOW); 
    digitalWrite(D12, LOW);    
    //delay(2); // waits for a 2 ms to simulate step deley // Moved outside the doStep method
   return;
  }

  stepCount++;

if (fullPower){
  switch(stepPOS){
    case 0:
    digitalWrite(D09, HIGH); 
    digitalWrite(D10, HIGH); 
    digitalWrite(D11, LOW); 
    digitalWrite(D12, LOW); 
    break;
    
    case 1:
    digitalWrite(D09, LOW); 
    digitalWrite(D10, HIGH); 
    digitalWrite(D11, HIGH); 
    digitalWrite(D12, LOW);
    break;
    
    case 2:
    digitalWrite(D09, LOW); 
    digitalWrite(D10, LOW); 
    digitalWrite(D11, HIGH); 
    digitalWrite(D12, HIGH);
    break;
    
    case 3:
    digitalWrite(D09, HIGH); 
    digitalWrite(D10, LOW); 
    digitalWrite(D11, LOW); 
    digitalWrite(D12, HIGH); 
    break;
  }
}else{
  switch(stepPOS){    
    case 0:
    digitalWrite(D09, HIGH); 
    digitalWrite(D10, LOW); 
    digitalWrite(D11, LOW); 
    digitalWrite(D12, LOW); 
    break;
    
    case 1:
    digitalWrite(D09, LOW); 
    digitalWrite(D10, HIGH); 
    digitalWrite(D11, LOW); 
    digitalWrite(D12, LOW);
    break;
    
    case 2:
    digitalWrite(D09, LOW); 
    digitalWrite(D10, LOW); 
    digitalWrite(D11, HIGH); 
    digitalWrite(D12, LOW);
    break;
    
    case 3:
    digitalWrite(D09, LOW); 
    digitalWrite(D10, LOW); 
    digitalWrite(D11, LOW); 
    digitalWrite(D12, HIGH); 
    break;
  }
}
  // Min delay is 2ms
  // delay(2); // waits for a 2 m2 // moved outside the doStep method
}

const byte motorStep = 3; // Pin 3
const byte motorDir  = 4; // Pin 4
const byte onOff  = 5;    // Pin 5
volatile byte state = LOW;
unsigned long loopCnt = 9999999;

long debouncing_time = 100; //Debouncing Time in Milliseconds
volatile unsigned long last_millis;

void pinIRInterrupt(){
  irCount++;
}

void interruptRotory() {
  int amount = 1;
  
  if((long)(millis() - last_millis) <= debouncing_time) {
    amount = 10;
    }
    
  last_millis = millis(); //micros();
  
  direction1 = digitalRead(directionPin); 
  if (direction1 == 1){
    if (rotoryCount + amount <= 9999){
      rotoryCount += amount;
    }
  }else{
    if (rotoryCount - amount > 0){
      rotoryCount -= amount;
    }
  }

  Serial.print  ("Interrupt: ");
  Serial.print  (direction1);
  Serial.print  (" rotoryCount: ");
  Serial.println(rotoryCount);
}

double toroidOD = 0.0;
double toroidID = 0.0;
double toroidHeight  = 0.0;
double wireWidth = 0.0;
int windings = 0;

int debounceSwitchMills = 100;
void debounceSwitch(){
  while(!digitalRead(rotorySwitch)){
    delay(debounceSwitchMills);
  }
  delay(debounceSwitchMills * 4);
}

void setOD(){
  lcd.clear();  
  lcd.setCursor(0, 0);
  lcd.print("Toroid Diameter");
  lcd.setCursor(0, 1);
  lcd.print("Outside:");

  rotoryCount = 1;
  rotoryCount = 493;
  toroidOD = -1;
  while(digitalRead(rotorySwitch)){
    tempRotoryCount = (double)rotoryCount / 10.0;
    if (tempRotoryCount !=  toroidOD){
      toroidOD = tempRotoryCount;
      lcd.setCursor(9, 1);
      lcdDouble(toroidOD, 1);
    }
  }
  debounceSwitch();

  Serial.print  ("toroidOD: ");
  Serial.println(toroidOD);
}

void setID(){
  lcd.clear();  
  lcd.setCursor(0, 0);
  lcd.print("Toroid Diameter");
  lcd.setCursor(0, 1);
  lcd.print("Inside:");

  rotoryCount = 1;
  rotoryCount = 314;
  toroidID = -1;
  while(digitalRead(rotorySwitch)){
    tempRotoryCount = (double)rotoryCount / 10.0;
    if (tempRotoryCount !=  toroidID){
      toroidID = tempRotoryCount;
      lcd.setCursor(9, 1);
      lcdDouble(toroidID, 1);
    }
  }
  debounceSwitch();

  Serial.print  ("toroidID: ");
  Serial.println(toroidID);
}

void setHeight(){
  lcd.clear();  
  lcd.setCursor(0, 0);
  lcd.print("Toroid");
  lcd.setCursor(0, 1);
  lcd.print("Height:");

  rotoryCount = 1;
  rotoryCount = 165;
  toroidHeight = -1;
  
  while(digitalRead(rotorySwitch)){
    tempRotoryCount = (double)rotoryCount / 10.0;
    if (tempRotoryCount !=  toroidHeight){
      toroidHeight = tempRotoryCount;
      lcd.setCursor(9, 1);
      lcdDouble(toroidHeight, 1);
    }
  }
  debounceSwitch();

  Serial.print  ("toroidHeight: ");
  Serial.println(toroidHeight);
}

void setWindings(){
  lcd.clear();  
  lcd.setCursor(0, 0);
  lcd.print("Toroid");
  lcd.setCursor(0, 1);
  lcd.print("Windings: ");

  rotoryCount = 1;
  rotoryCount = 500;
  windings = -1;
  while(digitalRead(rotorySwitch)){
    if (rotoryCount !=  windings){
      windings = rotoryCount;
      lcd.setCursor(10, 1);
      lcd.print(windings);
      lcd.print(" ");
    }
  }
  debounceSwitch();

  Serial.print  ("windings: ");
  Serial.println(windings);
}

void setWireWidth(){
  lcd.clear();  
  lcd.setCursor(0, 0);
  lcd.print("Wire");
  lcd.setCursor(0, 1);
  lcd.print("Width: ");

  rotoryCount = 1;
  rotoryCount = 64;//200;
  wireWidth = -1;
  while(digitalRead(rotorySwitch)){
    tempRotoryCount = (double)rotoryCount / 100.0;
    if (tempRotoryCount !=  wireWidth){
      wireWidth = tempRotoryCount;
      lcd.setCursor(9, 1);
      lcdDouble(wireWidth, 2);
    }
  }
  debounceSwitch();

  Serial.print  ("wireWidth: ");
  Serial.println(wireWidth);
}

void loadShuttle(){

  Serial.println("\n=====");
  Serial.println("Shuttle load:");
  Serial.println("-----");
  
  double toroidWidth = (toroidOD - toroidID) / 2;
  Serial.print  ("toroidWidth: ");
  Serial.println(toroidWidth);

  Serial.print  ("toroidHeight: ");
  Serial.println(toroidHeight);

  double toroidArea = (toroidWidth + toroidHeight) * 2;
  Serial.print  ("toroidArea: ");
  Serial.println(toroidArea);

  Serial.print  ("windings: ");
  Serial.println(windings);

  double mmOfWireNeeded = toroidArea * windings;
  Serial.print  ("mmOfWireNeeded: ");
  Serial.println(mmOfWireNeeded);

  double metersOfWireNeeded = mmOfWireNeeded / 1000;
  Serial.print  ("metersOfWireNeeded: ");
  Serial.println(metersOfWireNeeded);

  double shuttleWindings = ( mmOfWireNeeded / shuttleCircumference ) + 1;
  Serial.print  ("shuttleWindings: ");
  Serial.println(shuttleWindings);

  // load loops
  // number of overlaps
  lcd.clear();  
  lcd.setCursor(0, 0);
  lcd.print("Load Shuttle");

  lcd.setCursor(0, 1);
  lcd.print(metersOfWireNeeded);
  lcd.print("M of wire");

  while(digitalRead(rotorySwitch)){  
  }
  debounceSwitch();

  // Load the shuttle
  // run motor revers
  digitalWrite(motor1A, LOW); 
  digitalWrite(motor2A, HIGH); 
  digitalWrite(motorEnable, HIGH); 

  irCount = 0;
  int shuttleLast = -1;
  lcd.clear();  
  lcd.setCursor(0, 0);
  lcd.print("Wind Shuttle...");  
  while (irCount <= shuttleWindings){
    if (irCount != shuttleLast){
      shuttleLast = irCount;
      lcd.setCursor(0, 1);
      lcd.print("Loop: ");            
      lcd.print(irCount);            
      lcd.print("/");            
      lcd.print(shuttleWindings); 

      Serial.print("Loop: ");            
      Serial.print(irCount);            
      Serial.print("/");            
      Serial.println(shuttleWindings); 
    }
  }
  // Stop shuttle motor;
  digitalWrite(motorEnable, LOW); 
}

void windToroid(){
volatile unsigned long step_millis;

int waitMS = 50;

  Serial.println("\n=====");
  Serial.println("Wind Toroid:");
  Serial.println("-----");

delay(waitMS);

// calc some stuff
  double odToroidCircumference = toroidOD * PI;
  Serial.print  ("odToroidCircumference: ");
  Serial.println(odToroidCircumference);
delay(waitMS);

  double idToroidCircumference = toroidID * PI;
  Serial.print  ("idToroidCircumference: ");
  Serial.println(idToroidCircumference);
delay(waitMS);

  double toroidRatio = idToroidCircumference / odToroidCircumference;
  Serial.print  ("toroidRatio: ");
  printDouble(toroidRatio, 5);
  Serial.println("");
delay(waitMS);

  double toroidToPostDIff = odToroidCircumference / postCircumference;  
  Serial.print  ("toroidToPostDIff: ");
  printDouble(toroidToPostDIff, 5);
  Serial.println("");
delay(waitMS);

  double toroidStepsPerRotation = (360.0 / postStepDegree  * toroidToPostDIff);  
  Serial.print  ("toroidStepsPerRotation: ");
  Serial.println(toroidStepsPerRotation);
delay(waitMS);

  double toroidStepDegree = 360.0/toroidStepsPerRotation;
  Serial.print  ("toroidStepDegree: ");
  printDouble(toroidStepDegree, 5);
  Serial.println("");
delay(waitMS);

  Serial.print  ("stepSizeMM: ");
  double stepSizeMM = idToroidCircumference / toroidStepsPerRotation;
  printDouble(stepSizeMM, 5);
  Serial.println("");
          
delay(waitMS);

// ================================================ (keep this)
// Test each PerRev Steps to verify full circle.    (keep this)
// ================================================ (keep this)
//for (int x = 0 ; x < postStepsPerRev; x++){
//for (int x = 0 ; x < motorStepsPerRev; x++){
//  for (int x = 0 ; x < toroidStepsPerRotation; x++){
//    doStep(motion::CW);
//    delay(2); // waits for a 2 ms to simulate step deley // Moved outside the doStep method
//  }
//doStep(motion::STOP);

  lcd.clear();  
  lcd.setCursor(0, 0);
  lcd.print("Thread toroid");
  
  lcd.setCursor(0, 1);
  lcd.print("ouside under&up");

  double moveStepSizeMM = stepSizeMM;
  double moveSizeMM = stepSizeMM;

  Serial.print  ("moveStepSizeMM: ");
  printDouble(moveStepSizeMM, 5);
  Serial.println("");
  
  Serial.print  ("moveSizeMM: ");
  printDouble(moveSizeMM, 5);
  Serial.println("");

  while(digitalRead(rotorySwitch)){
  }
  debounceSwitch();

  // Load the Toroid & run motor forward
  digitalWrite(motor1A, HIGH); 
  digitalWrite(motor2A, LOW); 
  digitalWrite(motorEnable, HIGH); 

// =====================================================================================
// =====================================================================================
// =====================================================================================
// =====================================================================================
  stepCount = 0;
  irCount = 0;
  int toroidLast = -1;
  while (irCount <= windings){
    if (irCount != toroidLast){
      toroidLast = irCount;
    
      lcd.clear();  
      lcd.setCursor(0, 0);
      lcd.print("Winding Toroid...");

      lcd.setCursor(0, 1);
      lcd.print("Loop: ");            
      lcd.print(irCount);            
      lcd.print("/");            
      lcd.print((int)windings);            
  
      Serial.print("\nToroid: ");            
      Serial.print(irCount);            
      Serial.print(" of ");            
      Serial.print((int)windings); 

      moveSizeMM += wireWidth;
      Serial.print(" wsMM ");            
      Serial.print(moveSizeMM); 
    }

    // Increment Stepper motor based on wire width ever 2mS.
    if(millis() - step_millis >= 2) {

      step_millis = millis(); //micros();
  
      // ----->>> increment stepper, wire diameter on ID but step for OD to meet the wire width goal
      if (moveStepSizeMM < moveSizeMM){

        moveStepSizeMM += stepSizeMM;

        Serial.print  (" mssMM: ");
        Serial.print (moveStepSizeMM);

        // do stepper step.
        doStep(motion::CW);
      }
    }
    
    // ----->>> Pause for overlaps
    if(stepCount > toroidStepsPerRotation){
      digitalWrite(motorEnable, LOW); 
      Serial.println("\nOverlap Pause: ");
      doStep(motion::STOP);      
      stepCount = 0;
      lcd.clear();  

      lcd.setCursor(0, 0);
      lcd.print("Overlap:");
      lcd.setCursor(0, 1);
      lcd.print("Move wire across");
      while(digitalRead(rotorySwitch)){
      }
    debounceSwitch();
    digitalWrite(motorEnable, HIGH); 
    }
  }

// =====================================================================================
// =====================================================================================
// =====================================================================================
// =====================================================================================  
  
  // Stop motor;
  digitalWrite(motorEnable, LOW); 
  // Stop stepper;
  doStep(motion::STOP);
}

// LOOP function runs over and over again forever
void loop() {

  Serial.println("\n\n\n\==========================================");
  Serial.println("Toroid Data:");
  Serial.println("-----");
  
  setOD();  
  setID();  
  setHeight();  
  setWindings();
  setWireWidth();
  loadShuttle();
  windToroid();
  
  Serial.println("==========================================");  
  // do it again?
  Serial.println("\n\n\nDo it again!!!");
}
