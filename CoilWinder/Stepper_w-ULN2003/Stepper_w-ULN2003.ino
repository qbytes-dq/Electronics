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
  
  // 28BYJ-48 Gear Reduction Ratio
  double topRatios = (28.0/22.0)* (22.0/22.0) *(22.0/20.0); // gears on top *(28.0/22.0)*(22.0/20.0);
  double gearRatios = (32.0/9.0) * (22.0/11.0) * (26.0/9.0) * (31.0/10.0) * topRatios;
  
  // Stride Angle ： 5.625° x 1/64 datasheet is wrong
  // Stride Angle ： 11.25° x ~1/64 website above is correct

  // Cir
  #define PI 3.1415926535897932384626433832795  // Overkill.....
  double postCircumference = 22.5 * PI;
  double coilCircumference = 49.5 * PI;
  double shuttleCircumference = 184 * PI;
  
  double phys = coilCircumference/postCircumference;
  
  double fullRotationSteps = (360.0 / (11.25 / gearRatios) * phys);
    
  enum motion {UP, DOWN, STOP};
  void doStep(motion dir);
  
  int step = 0;

  const byte D09 =  9;
  const byte D10 = 10;
  const byte D11 = 11;
  const byte D12 = 12;

// ============================================================
// ============================================================
// ============================================================
 
  // ------------------------------------------------------
  // iterupt for IR winder loop counter 
  // ------------------------------------------------------
  const byte interruptPinIR = 2; // pin 2, Pin D2 = INT0
  volatile unsigned long loopCount = 0;
  
  // ------------------------------------------------------
  // interrupt for rotory encoder
  // ------------------------------------------------------
  const byte interruptRotoryPin = 3; // pin 3, Pin D3 = INT1
  const byte directionPin = 4;
  volatile byte direction1 = LOW;
  volatile int rotoryCount = 0;
  volatile double tempRotoryCount = 0.0;
  
  const byte rotorySwitch = 13;  // Pin 13


  // ------------------------------------------------------
  // LCD setup
  // ------------------------------------------------------
  // SDA is pin A4
  // SCL is pin A5
  #include <LiquidCrystal_I2C.h> //from newliquidcrystal library
  LiquidCrystal_I2C lcd(0x27, 20, 2);  // Set the LCD I2C address

void printDouble(double number, byte precision){
  // Make room for your floating point number, however you plan to format it.
  char floatBuffer[precision + 1];
  
  // Make room for entire print line, however long you plan
  // to make it.
  char printBuffer[precision + 1];

  dtostrf(number, precision, precision, floatBuffer);
  sprintf(printBuffer, "%s", floatBuffer);
  Serial.println(printBuffer);
}

void lcdDouble(double number, byte precision){
  // Make room for your floating point number, however you plan to format it.
  char floatBuffer[precision + 1];
  
  // Make room for entire print line, however long you plan
  // to make it.
  char printBuffer[precision + 1];

  dtostrf(number, precision, precision, floatBuffer);
  sprintf(printBuffer, "%s mm ", floatBuffer);

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

  Serial.println("Stepper 28BYJ-48 Gear Reduction with ULN2003 driver");
  Serial.println("=============================");


  Serial.print  ("Gear Ratios: ");
  Serial.println(gearRatios);
  Serial.print  ("Full Rotation Steps: ");
  Serial.println(fullRotationSteps);
  Serial.print  ("Step size: ");
  byte precision = 9;  // Number of digits after the decimal point
  printDouble(360.0/fullRotationSteps, precision);
 
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
  lcd.print("Coil Winder V0.2");

  lcd.setCursor(0, 1);
  lcd.print("Toolbox Aid");

  delay(3000);  
  //         12345678901234567890
  lcd.setCursor(0, 0);
  lcd.print("                    ");
  lcd.setCursor(0, 1);
  lcd.print("                    ");

//  lcd.setCursor(0, 1);
//  lcdDouble(360.0/fullRotationSteps, precision);
//  delay(3000);  
}

void doDisplay(){
  lcd.init();
  lcd.backlight();
  
//  lcd.clear();  
  
  lcd.setCursor(0, 0);
  lcd.print("Coil Winder");
  lcd.setCursor(0, 1);
  lcd.print("abc                 ");
}

void doStep(motion dir){
  if (dir == motion::UP){
    step++;
    if (step >=4)
      step = 0;
  }else if (dir == motion::DOWN){
    step--;
    if (step < 0){
      step = 3;
    }
  } else {//Stop
   // Do nothing
   delay(2); // waits for a 2 ms to simulate step deley
   return;
  }

  switch(step){
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

  switch(step){
//    case 0:
//    digitalWrite(D09, HIGH); 
//    digitalWrite(D10, HIGH); 
//    digitalWrite(D11, LOW); 
//    digitalWrite(D12, LOW); 
//    break;
//    
//    case 1:
//    digitalWrite(D09, LOW); 
//    digitalWrite(D10, HIGH); 
//    digitalWrite(D11, HIGH); 
//    digitalWrite(D12, LOW);
//    break;
//    
//    case 2:
//    digitalWrite(D09, LOW); 
//    digitalWrite(D10, LOW); 
//    digitalWrite(D11, HIGH); 
//    digitalWrite(D12, HIGH);
//    break;
//    
//    case 3:
//    digitalWrite(D09, HIGH); 
//    digitalWrite(D10, LOW); 
//    digitalWrite(D11, LOW); 
//    digitalWrite(D12, HIGH); 
//    break;
  }
  // Min delay is 2ms
  delay(2); // waits for a 2 m2
}

const byte motorStep = 3;
const byte motorDir  = 4;
const byte onOff  = 5;
volatile byte state = LOW;
unsigned long loopCnt = 9999999;

long debouncing_time = 100; //Debouncing Time in Milliseconds
volatile unsigned long last_millis;

void pinIRInterrupt(){
  loopCount++;
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
double toroidH  = 0.0;
int windings = 0;
double wireWidth = 0;


int debounceDelay = 100;
void debounceSwitch(){
  while(!digitalRead(rotorySwitch)){
    delay(debounceDelay);
  }
  delay(debounceDelay * 4);
}

void setOD(){
  lcd.setCursor(0, 0);
  lcd.print("Toroid");
  lcd.setCursor(0, 1);
  lcd.print("OD:");

  rotoryCount = 1;
  rotoryCount = 493;
  
  while(digitalRead(rotorySwitch)){
    tempRotoryCount = (double)rotoryCount / 10.0;
    if (tempRotoryCount !=  toroidOD){
      toroidOD = tempRotoryCount;
      lcd.setCursor(6, 1);
      lcdDouble(toroidOD, 1);
    }
  }
  debounceSwitch();
}

void setID(){
  lcd.setCursor(0, 0);
  lcd.print("Toroid");
  lcd.setCursor(0, 1);
  lcd.print("ID:");

  rotoryCount = 1;
  rotoryCount = 314;
  while(digitalRead(rotorySwitch)){
    tempRotoryCount = (double)rotoryCount / 10.0;
    if (tempRotoryCount !=  toroidID){
      toroidID = tempRotoryCount;
      lcd.setCursor(6, 1);
      lcdDouble(toroidID, 1);
    }
  }
  debounceSwitch();
}

void setH(){
  lcd.setCursor(0, 0);
  lcd.print("Toroid");
  lcd.setCursor(0, 1);
  lcd.print("H:");

  rotoryCount = 1;
  rotoryCount = 165;
  while(digitalRead(rotorySwitch)){
    tempRotoryCount = (double)rotoryCount / 10.0;
    if (tempRotoryCount !=  toroidH){
      toroidH = tempRotoryCount;
      lcd.setCursor(6, 1);
      lcdDouble(toroidH, 1);
    }
  }
  debounceSwitch();
}

void setWindings(){
  lcd.setCursor(0, 0);
  lcd.print("Toroid");
  lcd.setCursor(0, 1);
  lcd.print("Windings: ");

  rotoryCount = 1;
  rotoryCount = 100;
  while(digitalRead(rotorySwitch)){
    if (rotoryCount !=  windings){
      windings = rotoryCount;
      lcd.setCursor(10, 1);
      lcd.print(windings);
      lcd.print(" ");
    }
  }
  debounceSwitch();
}

void setWireWidth(){
  lcd.setCursor(0, 0);
  lcd.print("Toroid wire");
  lcd.setCursor(0, 1);
  lcd.print("Width: ");

  rotoryCount = 1;
  rotoryCount = 64;
  while(digitalRead(rotorySwitch)){
    tempRotoryCount = (double)rotoryCount / 100.0;
    if (tempRotoryCount !=  wireWidth){
      wireWidth = tempRotoryCount;
      lcd.setCursor(8, 1);
      lcdDouble(wireWidth, 2);
    }
  }
  debounceSwitch();
}

void loadShuttle(){
  lcd.setCursor(0, 0);
  lcd.print("Load Shuttle");
  lcd.setCursor(0, 1);
  lcd.print("M/W: ");

  
  // meters required
  double toroidW = (toroidOD - toroidID) / 2;
  Serial.print  ("toroidW: ");
  Serial.println(toroidW);

  double area = (toroidW + toroidH) * 2;
  Serial.print  ("area: ");
  Serial.println(area);

  double milli = (area * windings);
  Serial.print  ("milli: ");
  Serial.println(milli);

  Serial.print  ("Shuttle Circum: ");
  Serial.println(shuttleCircumference);

  double shuttleWindings = milli / shuttleCircumference;
  Serial.print  ("shuttleWindings: ");
  Serial.println(shuttleWindings);

  double meters = milli / 1000;
  Serial.print  ("Meters: ");
  Serial.println(meters);

  // load loops
  // number of overlaps
  lcd.print(meters);
  lcd.print("/");
  lcd.print(shuttleWindings);

  Serial.print  ("Shuttle Windings: ");
  Serial.println(shuttleWindings);



  while(digitalRead(rotorySwitch)){
  
  }
  debounceSwitch();

  // Load the shuttle
  // run motor revers
  // count loops +1
  // stop motor;
}

void   loadWindToroid(){
  lcd.setCursor(0, 0);
  lcd.print("Wind Coil");
  lcd.setCursor(0, 1);
  lcd.print("Loop / ETA : ");

  // load loops
  // pause for overlaps

  while(digitalRead(rotorySwitch)){
  
  }
  debounceSwitch();

  // Load the shuttle
  // run motor revers
  // count loops +1
  // increment stepper (wire diameter on ID but step for OD to meet the goal)
  // stop motor;
}


// LOOP function runs over and over again forever
void loop() {

  setOD();  
  setID();  
  setH();  
  setWindings();
  setWireWidth();
  loadShuttle();
  loadWindToroid();
  
  
  doDisplay();

  lcd.setCursor(0, 1);
  lcd.print("rotoryCount:       ");
  lcd.setCursor(6, 1);
  lcd.print(rotoryCount);
      
  lcd.setCursor(10, 1);
  lcd.print(loopCount);


  while (true){
    digitalWrite(motor1A, LOW); 
    digitalWrite(motor2A, HIGH); 
    digitalWrite(motorEnable, HIGH); 
//    delay(2000); // waits for a 2 ms to simulate step deley
while (digitalRead(rotorySwitch));
    digitalWrite(motorEnable, LOW); 
    delay(1000); // waits for a 2 ms to simulate step deley

  
    digitalWrite(motor1A, HIGH); 
    digitalWrite(motor2A, LOW); 
    digitalWrite(motorEnable, HIGH); 
//    delay(2000); // waits for a 2 ms to simulate step deley
while (digitalRead(rotorySwitch));
    digitalWrite(motorEnable, LOW); 
    delay(1000); // waits for a 2 ms to simulate step deley
    }

  
  // put your main code here, to run repeatedly:
  
  for (int l = 0; l < fullRotationSteps; l++){
    doStep(motion::UP);
  }
  for (int l = 0; l < (fullRotationSteps/4); l++){
    doStep(motion::STOP);
  } 
  for (int l = 0; l < fullRotationSteps; l++){
    doStep(motion::DOWN);
  }    
  for (int l = 0; l < (fullRotationSteps/4); l++){
    doStep(motion::STOP);
  } 
}
