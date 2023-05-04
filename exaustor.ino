#include "Util.h"
#define P_OUT_BANHEIRO 2
#define P_OUT_LAVABO 3
#define P_OUT_EXAUSTOR 4

#define P_IN_LAVABO 5
#define P_IN_BANHEIRO 6
#define P_IN_QUARTO 7
#define TIMER_3 8640000 //24h
#define PERIODO_LIGADO 1800000 //30 min

//#define TIMER_3 10000 //24h
//#define PERIODO_LIGADO 5000 //30 min

#define TEMPO_DELAY 100
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
 
bool lampadaBanheiroLigada =true;
bool estadoSuitchBanheiro =HIGH;
bool estadoSuitchQuarto =HIGH;
Util util;
void setup() {
  util.iniciaTimer3(TIMER_3);
  util.iniciaTimer4(PERIODO_LIGADO);

  pinMode(P_IN_BANHEIRO,INPUT_PULLUP);
  pinMode(P_IN_QUARTO,INPUT_PULLUP);
  pinMode(P_IN_LAVABO,INPUT_PULLUP);

 pinMode(P_OUT_BANHEIRO,OUTPUT);
 pinMode(P_OUT_EXAUSTOR,OUTPUT);
 pinMode(P_OUT_LAVABO,OUTPUT);
  
 //digitalWrite(P_OUT_BANHEIRO, HIGH);
 //digitalWrite(P_OUT_EXAUSTOR, HIGH);
 //digitalWrite(P_OUT_LAVABO, LOW);
}
//void(* resetFunc) (void) = 0; //declare reset function @ address 0

void loop() {

      if (isAcionouSuitchBanheiro() || isAcionouSuitchQuarto()){
          ligarDesligarBanheiro();
      }

      if (isSuitchLavaboOn()){
          ligarLavabo();
      }else   desligarLavabo();
  

      if (lampadaBanheiroLigada || isSuitchLavaboOn()){
          ligarExaustor();
      }else desligarExaustor();

    

    if (util.saidaTimer3()) {
          
          if (!lampadaBanheiroLigada){
  
              ligarDesligarBanheiro();
          }
    }

    if (util.saidaTimer4()) {

          if (lampadaBanheiroLigada){
  
              ligarDesligarBanheiro();
          }
    }


}

void desligarExaustor(){
  digitalWrite(P_OUT_EXAUSTOR, HIGH);
  //resetFunc();

}
void ligarExaustor(){
  
  digitalWrite(P_OUT_EXAUSTOR, LOW);
 
}  

void ligarDesligarBanheiro(){

    util.reIniciaTimer3();
    util.reIniciaTimer4();

   digitalWrite(P_OUT_BANHEIRO, lampadaBanheiroLigada);
   lampadaBanheiroLigada = !lampadaBanheiroLigada;
         
}
void desligarLavabo(){
  
   digitalWrite(P_OUT_LAVABO, HIGH);

  
  }

void ligarLavabo(){

   digitalWrite(P_OUT_LAVABO, LOW);

}

bool isAcionouSuitchBanheiro(){
  
      if (estadoSuitchBanheiro != util.debounce(P_IN_BANHEIRO)){
          util.bloquear(TEMPO_DELAY);
          if (estadoSuitchBanheiro != util.debounce(P_IN_BANHEIRO)){
              estadoSuitchBanheiro = util.debounce(P_IN_BANHEIRO);
              return true;
          }
      }else return false;
 
}

bool isAcionouSuitchQuarto(){
  
  if (estadoSuitchQuarto != util.debounce(P_IN_QUARTO)){
      util.bloquear(TEMPO_DELAY);
      if (estadoSuitchQuarto != util.debounce(P_IN_QUARTO)){
         estadoSuitchQuarto = util.debounce(P_IN_QUARTO);
         return true;
      }         
  }else return false;
 
}


bool isSuitchLavaboOn(){

        if (util.debounce(P_IN_LAVABO)){
             util.bloquear(TEMPO_DELAY);
             return util.debounce(P_IN_LAVABO);
             }
         return false;
 

}

 
