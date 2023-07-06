const int ldrPin1 = A0; 
const int ldrPin2 = A1;
int LightInt[2] = {0, 0};
const float Tresh = 0.7;




const int segmentPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, A2, A3};

int hello[][14] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   
  {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},   // O
  {0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0},   // LO
  {0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0},   // LL
  {1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0},   // EL
  {0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1},   // HE
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1},   //  H
};

int bye[][14] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},   // b
  {0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1},   // bY
  {0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1},   // YE
  {1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},   // E
};

int omsim[][14] = {
  {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0,}   // 00
};

void printHello(int number){
  for (int i=0; i<14; i++){
    digitalWrite(segmentPins[i], hello[number][i]);
    
  }
}

void printBye(int number){
  for (int i=0; i<14; i++){
    digitalWrite(segmentPins[i], bye[number][i]);
  }
}

void printZero(int number){
  for (int i=0; i<14; i++){
    digitalWrite(segmentPins[i], omsim[number][i]);
  }
}

void setup() {
  Serial.begin(9600); 
  pinMode(ldrPin1, INPUT);  
  pinMode(ldrPin2, INPUT);

  LightInt[0] = analogRead(ldrPin1);
  LightInt[1] = analogRead(ldrPin2);
}

void loop() {

  float Val[2] = {Tresh*LightInt[0], Tresh*LightInt[1]};
  
  int ldrStatus1 = analogRead(ldrPin1);
  int ldrStatus2 = analogRead(ldrPin2);
  
  if (ldrStatus1 >= Val[0] && ldrStatus2 <Val[1]){
  	for(int i=0; i<7; i++){
    	printHello(i);
    	delay(750);
      	Serial.print("LDR1 IS ON");
  	};
  }
  if (ldrStatus2 >= Val[1] && ldrStatus1 <Val[0]){
    for (int i=0; i<5; i++){
      printBye(i);
      delay(750);
      Serial.print("LDR2 IS ON");
    }
  }
  
  else if (ldrStatus1 >= Val[0] && ldrStatus2 >= Val[1]){
    int i=0;
    printZero(i);
    Serial.print("LDR1 AND LDR2 IS ON");
  }
  
  else if (ldrStatus1 < Val[0] && ldrStatus2 < Val[1]){
    int i=0;
    printZero(i);
    Serial.print("LDR1 AND LDR2 IS OFF");
  }
}