// Shared cathodes demo
// Dan Royer (dan@marginallyclever.com) 2017-02-16

#define PINA 2
#define PINB 3
#define PINC 4
#define PIND 5

// 4 wires, 16 combinations of on/off
#define COMBINATIONS (4*4)

#define WAIT 250


void setup() {
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
}


void loop() {
  int i,j;

  for(i=0;i<COMBINATIONS;++i) {
    lightPin(i,1,PINA);
    lightPin(i,2,PINB);
    lightPin(i,4,PINC);
    lightPin(i,8,PIND);
    delay(WAIT);
  }
}


void lightPin(int data,int mask, int pin) {
  int state = (( data & mask )!=0) ? HIGH : LOW;
  digitalWrite(pin,state);
}

