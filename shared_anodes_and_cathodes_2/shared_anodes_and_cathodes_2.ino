// Shared anodes and cathodes demo
// Dan Royer (dan@marginallyclever.com) 2017-02-16

// anodes demo:   connect 4 anodes to 5v and each cathode separately to pins 2,3,4,5.
// when voltage is high on a cathode electricity cannot flow through the LED, so it turns off.
// high voltage on the input pins is like equalized pressure in a water pipe (no flow).

// cathodes demo: connect 4 cathode to 5v and each anode separately to pins 2,3,4,5.
// when voltage is high on an anode electricity flows through the LED, so it turns on.
// the shortest route for current to flow is through the digital pins.  (like water doesn't flow uphill)


#define ANOA 2
#define ANOB 3
#define ANOC 4
#define ANOD 5

#define CATA 8
#define CATB 9
#define CATC 10
#define CATD 11

// 4 wires, 16 combinations of on/off
#define NUM_CATHODES (4)
#define NUM_ANODES   (4)
#define NUM_LIGHTS   (NUM_CATHODES*NUM_ANODES)
#define COMBINATIONS (NUM_LIGHTS*NUM_LIGHTS)

#define WAIT 100


void setup() {
  pinMode(ANOA,OUTPUT);
  pinMode(ANOB,OUTPUT);
  pinMode(ANOC,OUTPUT);
  pinMode(ANOD,OUTPUT);
  
  pinMode(CATA,OUTPUT);
  pinMode(CATB,OUTPUT);
  pinMode(CATC,OUTPUT);
  pinMode(CATD,OUTPUT);
}

void loop() {
  countUp();
  oneAtATimeA();
  oneAtATimeB();
}


void oneAtATimeA() {
  int i;
  
  for(i=0;i<NUM_LIGHTS;++i) {
    digitalWrite(ANOA,          i< 4?HIGH:LOW); 
    digitalWrite(ANOB, i>= 4 && i< 8?HIGH:LOW); 
    digitalWrite(ANOC, i>= 8 && i<12?HIGH:LOW); 
    digitalWrite(ANOD, i>=12 && i<16?HIGH:LOW); 

    digitalWrite(CATA, (i%4)!=0 ?HIGH:LOW); 
    digitalWrite(CATB, (i%4)!=1 ?HIGH:LOW); 
    digitalWrite(CATC, (i%4)!=2 ?HIGH:LOW); 
    digitalWrite(CATD, (i%4)!=3 ?HIGH:LOW); 

    delay(analogRead(A0));  // read the potentiometer and adjust the speed.
  } 
}


void oneAtATimeB() {
  int i;
  
  for(i=0;i<NUM_LIGHTS;++i) {
    digitalWrite(CATA, !(         i< 4)?HIGH:LOW); 
    digitalWrite(CATB, !(i>= 4 && i< 8)?HIGH:LOW); 
    digitalWrite(CATC, !(i>= 8 && i<12)?HIGH:LOW); 
    digitalWrite(CATD, !(i>=12 && i<16)?HIGH:LOW); 

    digitalWrite(ANOA, (i%4)==0 ?HIGH:LOW); 
    digitalWrite(ANOB, (i%4)==1 ?HIGH:LOW); 
    digitalWrite(ANOC, (i%4)==2 ?HIGH:LOW); 
    digitalWrite(ANOD, (i%4)==3 ?HIGH:LOW); 

    delay(analogRead(A0));  // read the potentiometer and adjust the speed.
  } 
}


void countUp() {
  int i;

  for(i=0;i<COMBINATIONS;++i) {
    lightAnodeMask(i,1,ANOA);
    lightAnodeMask(i,2,ANOB);
    lightAnodeMask(i,4,ANOC);
    lightAnodeMask(i,8,ANOD);

    lightCathodeMask(i,16,CATA);
    lightCathodeMask(i,32,CATB);
    lightCathodeMask(i,64,CATC);
    lightCathodeMask(i,128,CATD);
    
    delay(analogRead(A0));  // read the potentiometer and adjust the speed.
  }
}


void lightAnodeMask(int data,int mask, int pin) {
  int state = (( data & mask )!=0) ? HIGH : LOW;
  digitalWrite(pin,state);
}


// cathodes are reversed:
// turn off the ones we want to light up.
// turn on the ones we want to prevent from lighting up.
void lightCathodeMask(int data,int mask, int pin) {
  int state = (( data & mask )!=0) ? LOW : HIGH;
  digitalWrite(pin,state);
}

