#define P_OUT_BANHEIRO 2
#define P_OUT_LAVABO 3
#define P_OUT_EXAUSTOR 4

#define P_IN_LAVABO 5
#define P_IN_BANHEIRO 6
#define P_IN_QUARTO 7


//1 ___________________ 10
//  * * * * * * * * * * MACHO

//IN
//1 = D7 QUARTO;
//2 = D6 BANHEIRO;
//3 = D5 LAVABO;

//4 = GND;

// FASE 1 FASE 2
//5 = F1;
//6 = F2;

//OUT
//7 = D4 EXAUSTOR;
//8 = D3 LAVABO;
//9 = D2 BANHEIRO
 
bool lampadaBanheiroLigada =false;
bool estadoSuiteBanheiro =HIGH;
bool estadoSuiteQuarto =HIGH;
void setup() {
  // put your setup code here, to run once:
  pinMode(P_IN_BANHEIRO,INPUT_PULLUP);
  pinMode(P_IN_QUARTO,INPUT_PULLUP);
  pinMode(P_IN_LAVABO,INPUT_PULLUP);
  Serial.begin(2000000);

 pinMode(P_OUT_BANHEIRO,OUTPUT);
 pinMode(P_OUT_EXAUSTOR,OUTPUT);
 pinMode(P_OUT_LAVABO,OUTPUT);
  
 digitalWrite(P_OUT_BANHEIRO, LOW);
 digitalWrite(P_OUT_EXAUSTOR, LOW);
 digitalWrite(P_OUT_LAVABO, LOW);
}

void loop() {

      if (lampadaBanheiroLigada || isSuiteLavaboOn()){
          ligarExaustor();
      }else desligarExaustor();

      if (isAcionouSuiteBanheiro() || isAcionouSuiteQuarto()){
          ligarDesligarBanheiro();
      }
      if (isSuiteLavaboOn()){
          ligarLavabo();
      }else   desligarLavabo();
  
    // put your main code here, to run repeatedly:

}

void desligarExaustor(){
  
  digitalWrite(P_OUT_EXAUSTOR, LOW);
  delay(100);
  Serial.println("DESLIGA EXAUSTOR ");

}
void ligarExaustor(){

  digitalWrite(P_OUT_EXAUSTOR, HIGH);
  delay(100); 
  Serial.println("LIGA EXAUSTOR ");

}

void ligarDesligarBanheiro(){
  lampadaBanheiroLigada = !lampadaBanheiroLigada;
  digitalWrite(P_OUT_BANHEIRO, lampadaBanheiroLigada);
  delay(100);
  Serial.print("LUZ Banheeiro: ");
  Serial.println(lampadaBanheiroLigada);
}
void desligarLavabo(){
   digitalWrite(P_OUT_LAVABO, LOW);
   delay(100);
  Serial.println("DESLIGA LAVABO ");
  
  }

void ligarLavabo(){
   digitalWrite(P_OUT_LAVABO, HIGH);
   delay(100);
  Serial.println("LIGA LAVABO");
}

bool isAcionouSuiteBanheiro(){
  
  if (estadoSuiteBanheiro != digitalRead(P_IN_BANHEIRO)){
      estadoSuiteBanheiro = digitalRead(P_IN_BANHEIRO);
      return true;
  }else return false;
 
}

bool isAcionouSuiteQuarto(){
  
  if (estadoSuiteQuarto != digitalRead(P_IN_QUARTO)){
      estadoSuiteQuarto = digitalRead(P_IN_QUARTO);
      return true;
  }else return false;
 
}


bool isSuiteLavaboOn(){

 return !digitalRead(P_IN_LAVABO);
 
}
