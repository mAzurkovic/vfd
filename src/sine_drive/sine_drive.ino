#define PWM_A 9
#define PWM_B 10
#define PWM_C 11

const int potPin = A1;
// Variables
int pwmSin[] = {127,110,94,78,64,50,37,26,17,10,4,1,0,1,4,10,17,26,37,50,64,78,94,110,127,144,160,176,191,204,217,228,237,244,250,253,255,253,250,244,237,228,217,204,191,176,160,144,127}; // array of PWM duty values for 8-bit timer - sine function
int currentStepA=0;
int currentStepB=16;
int currentStepC=32;
int pos;

//SETUP
void setup() {
  Serial.begin(9600);
//next commands will change the PWM frequency, so the annoying sound generated can be moved above human ear capability.
  TCCR0B = TCCR0B & 0b11111000 | 0x03 ;// changing this will also affect millis() and delay(), better to leave it default (0x03).
  TCCR1B = TCCR1B & 0b11111000 | 0x01; // set PWM frequency @ 31250 Hz for Pins 9 and 10, (0x03 is default value, gives 490 Hz).
  TCCR2B = TCCR2B & 0b11111000 | 0x01; // set PWM frequency @ 31250 Hz for Pins 11 and 3, (0x03 is default value, gives 490 Hz).
  
  ICR1 = 255 ; // 8 bit resolution for PWM
 
  pinMode(PWM_A, OUTPUT);
  pinMode(PWM_B, OUTPUT);
  pinMode(PWM_C, OUTPUT);

}
 
void loop() {
  move();
}
 
void move()
{
  currentStepA = currentStepA + 1;  //Add 1 to make the motor move step by step.
  currentStepB = currentStepA + 16; //add 120 deg of phase to whatever position StepA is. 
  currentStepC = currentStepA + 32; //add 240 deg of phase to whatever position StepA is.
  
  currentStepA = currentStepA%48; //I used remainder operation or modulo to "wrap" the values between 0 and 47
  currentStepB = currentStepB%48;
  currentStepC = currentStepC%48;

  Serial.println(pwmSin[currentStepA]);

  // To compute sine wave frequency:
  // T = 1/f, then since we have 48 steps in the look-up table, 
  // delay(T/48 * 1000), i.e. for 60 Hz, delay( (1/60) / 48 * 1000 )
  delay(208);

}
