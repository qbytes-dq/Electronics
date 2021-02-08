  // ------------------------------------------------------
  // Set serial port baud
  // ------------------------------------------------------
  unsigned long baudRate = 115200;


  // ------------------------------------------------------
  // initialize winder gear.
  // ------------------------------------------------------
    const byte motorEnable =  A0;
    const byte motor1A =  A1;
    const byte motor2a =  A2;

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
  double gearRatios = (32.0/9.0) * (22.0/11.0) * (26.0/9.0) * (31.0/10.0) *(28.0/22.0)*(22.0/20.0); // gears on top *(28.0/22.0)*(22.0/20.0);
  
  // Stride Angle ： 5.625° x 1/64 datasheet is wrong
  // Stride Angle ： 11.25° x ~1/64 website above is correct

  // Cir
  #define PI 3.1415926535897932384626433832795
  double postCircumference = 22.5 * PI;
  double coilCircumference = 49.5 * PI;
  //double phys = 154.97/70.69;  //22.5/49.33
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

/*
 *   Pin D2 = INT0
 *   Pin D3 = INT1
 */
 
  // ------------------------------------------------------
  // iterupt for IR winder loop counter 
  // ------------------------------------------------------
  const byte interruptPinIR = 2; // pin 2
  volatile unsigned long loopCount = 0;
  
  // ------------------------------------------------------
  // interrupt for rotory encoder
  // ------------------------------------------------------
  const byte interruptRotoryPin = 3; // pin 3
  const byte directionPin = 4;
  volatile byte direction1 = LOW;
  volatile unsigned long count = 0;
  
  const byte rotorySwitch = 13;  // Pin 13


  // ------------------------------------------------------
  // LCD setup
  // ------------------------------------------------------
  // SDA is pin A4
  // SCL is pin A5
  #include <LiquidCrystal_I2C.h> //from newliquidcrystal library
  LiquidCrystal_I2C lcd(0x27, 20, 2);  // Set the LCD I2C address



void printDouble( double val, unsigned int precision){
// Prints val with number of decimal places determine by precision
// NOTE: precision is 1 followed by the number of zeros for the desired number of decimial places
// example: printDouble( 3.1415, 100); // prints 3.14 (two decimal places)

   Serial.print (int(val));  //prints the int part
   Serial.print("."); // print the decimal point
   unsigned int frac;
   if(val >= 0)
       frac = (val - int(val)) * precision;
   else
       frac = (int(val)- val ) * precision;
   Serial.println(frac,DEC) ;
}

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
  printDouble((360.0/fullRotationSteps),10000);

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
  
  
  dtostrf((360.0/fullRotationSteps), precision+3, precision, floatBuffer);
  sprintf(printBuffer, "With %%.%df precision, Step size = %s", precision, floatBuffer);
  Serial.println(printBuffer);


  // ------------------------------------------------------
  // initialize winder gear.
  // ------------------------------------------------------
  pinMode(motorEnable, OUTPUT);
  pinMode(motor1A, OUTPUT);
  pinMode(motor2a, OUTPUT);
      
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
  lcd.print("Coil Winder V0.1");

  lcd.setCursor(0, 1);
  //lcd.print("Q-Bytes World");
  lcd.print("Toolbox Aid");

  delay(3000);  
}

void doDisplay(){
  lcd.init();
  lcd.backlight();
  
  //delay(2000);  
  lcd.clear();  
  
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

volatile boolean activeRun = false;
long debouncing_time = 100; //Debouncing Time in Milliseconds
volatile unsigned long last_millis;
volatile int b=0;

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
// 
//  if (loopCnt >= gear2StepsPerRev){
//    loopCnt = 0;
//    activeRun = true;
//    Serial.print("arT:");   
//  }    

  Serial.print(state);   
  Serial.print(":");   
  Serial.println(activeRun);  
}

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
    count += amount;
  }else{
    count -= amount;
  }


  Serial.print  ("Interrupt: ");
  Serial.print  (direction1);

  Serial.print  ("Interrupt: ");
  Serial.print  (direction1);
  Serial.print  (" cnt: ");
  Serial.println(count);
}

//void debounceInterrupt() {
//  if((long)(millis() - last_millis) >= debouncing_time * 1000) {
//    Interrupt();
//    cntDetectIR();
//    last_millis = millis(); //micros();
//  }else{
//    Serial.println ("early");
//    return;
//  }
//
//  Serial.print ("Debounce Time: ");
//  Serial.println (debouncing_time * 1000);
//    
//  Serial.print ("last_micros Time: ");
//  Serial.println (last_millis);
//}


// LOOP function runs over and over again forever
void loop() {

  doDisplay();

  lcd.setCursor(0, 1);
  lcd.print("Count:       ");
  lcd.setCursor(6, 1);
  lcd.print(count);
      
  lcd.setCursor(10, 1);
  lcd.print(loopCount);


  while (true){
    digitalWrite(motor1A, LOW); 
    digitalWrite(motor2a, HIGH); 
    digitalWrite(motorEnable, HIGH); 
//    delay(2000); // waits for a 2 ms to simulate step deley
while (digitalRead(rotorySwitch));
    digitalWrite(motorEnable, LOW); 
    delay(1000); // waits for a 2 ms to simulate step deley

  
    digitalWrite(motor1A, HIGH); 
    digitalWrite(motor2a, LOW); 
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
