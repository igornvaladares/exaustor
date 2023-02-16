#include "Util.h"
#define P_OUT_BANHEIRO 2
#define P_OUT_LAVABO 3
#define P_OUT_EXAUSTOR 4

#define P_IN_LAVABO 5
#define P_IN_BANHEIRO 6
#define P_IN_QUARTO 7
#define TIMER_3 1800000
#define TEMPO_DELAY 0
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
bool estadoSuitchBanheiro =HIGH;
bool estadoSuitchQuarto =HIGH;
bool desligarLavaboForcado = false;
Util util;
void setup() {
  util.iniciaTimer3(TIMER_3);
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

      if (lampadaBanheiroLigada || isSuitchLavaboOn()){
          ligarExaustor();
      }else desligarExaustor();

      if (isAcionouSuitchBanheiro() || isAcionouSuitchQuarto()){
          ligarDesligarBanheiro();
      }
      if (isSuitchLavaboOn()){
          ligarLavabo();
      }else   desligarLavabo();
  

    if (lampadaBanheiroLigada){

      if (util.saidaTimer3()){
            ligarDesligarBanheiro();
      }

    }else util.reIniciaTimer3();
  

}

void desligarExaustor(){
  
  digitalWrite(P_OUT_EXAUSTOR, LOW);
  Serial.println("DESLIGA EXAUSTOR ");

}
void ligarExaustor(){

  digitalWrite(P_OUT_EXAUSTOR, HIGH);
  delay(TEMPO_DELAY);
  Serial.println("LIGA EXAUSTOR ");

}

void ligarDesligarBanheiro(){
  lampadaBanheiroLigada = !lampadaBanheiroLigada;
  digitalWrite(P_OUT_BANHEIRO, lampadaBanheiroLigada);
  delay(TEMPO_DELAY);
  Serial.print("LUZ Banheeiro: ");
  Serial.println(lampadaBanheiroLigada);
}
void desligarLavabo(){
   digitalWrite(P_OUT_LAVABO, LOW);
  Serial.println("DESLIGA LAVABO ");
  
  }

void ligarLavabo(){
   digitalWrite(P_OUT_LAVABO, HIGH);
   Serial.println("LIGA LAVABO");
}

bool isAcionouSuitchBanheiro(){
  
  if (estadoSuitchBanheiro != debounce(P_IN_BANHEIRO)){
      estadoSuitchBanheiro = debounce(P_IN_BANHEIRO);
      return true;
  }else return false;
 
}

bool isAcionouSuitchQuarto(){
  
  if (estadoSuitchQuarto != debounce(P_IN_QUARTO)){
      estadoSuitchQuarto = debounce(P_IN_QUARTO);
      return true;
  }else return false;
 
}


bool isSuitchLavaboOn(){

 return debounce(P_IN_LAVABO);
 

}
boolean debounce(int pin)
  {
    boolean current = !digitalRead(pin);      // le o estado atual do botao
    
    if(!current)
    {
      delay(3);     // espera 3ms --> AQUI VAI O "SEGREDO" DO "EFETIVO E SEGURO, ALÉM DE RÁPIDO DEBOUNCING"
      current = !digitalRead(pin);      // le NOVAMENTE o estado do botao apos o "debounce"  
    }
    return current;     // retorna o valor atualizado do botao (button)
  }
 
 
