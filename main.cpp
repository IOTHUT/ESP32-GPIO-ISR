#include <Arduino.h>


#define IO_ISR_PIN 0                //define pino para interrupção
volatile bool hasInterrupt = false; //variavel auxiliar 
                                    //(altera para true quando gerada interrupcao)


void IRAM_ATTR generatedISR() { //função executada quando uma interrupção ocorre..
  //tratamento da interrupção
  hasInterrupt = true;         
}


void setup() {
  Serial.begin(115200);
  //configura pino (IO_ISR_PIN) selecionado para gerar interrupção 
  //quando o nível lógica muda de HIGH para LOW (FALLING EDGE)

  attachInterrupt(IO_ISR_PIN, generatedISR, FALLING);

}

void loop() {

  static short int loop_count = 0;

  if(hasInterrupt ) {                     //caso o estado da variavel mude para TRUE
    hasInterrupt = false;                 //garante que no proximo ciclo não entrará novamente na condição

    Serial.println("interrupcao gerada"); //debug
    Serial.println("funcao longa -> inicio");   
    delay(1000);                          //simula uma função que leva um longo tempo para ser concluida
    Serial.println("funcao longa -> fim");      
  }

  loop_count++; //incrementa 10x por segundo
  delay(100);

  Serial.println("loop_count -> " + String(loop_count));
 
}