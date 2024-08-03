const int pinoLed = 13; // Define o pino digital para o LED
int estadoLed = LOW; // Inicializa o estado do LED como LOW (desligado)
int vermelho = 8; // Define o pino digital para o botão vermelho
int azul = 9; // Define o pino digital para o botão azul
unsigned long tempoAnterior = 0; // Variável para armazenar o tempo anterior
const long intervalo = 1000; // Intervalo de 1 segundo
int segundos = 0; // Variável para contar os segundos
int minutos = 0; // Variável para contar os minutos
bool botaoPressionado = 0; // Variável para indicar se o botão foi pressionado
unsigned long tempoInicio = 0; // Variável para armazenar o tempo de início

#include <LiquidCrystal.h>; // Inclui a biblioteca LiquidCrystal
LiquidCrystal lcd(12,11,5,4,3,2); // Inicializa o objeto lcd

void setup() {
  pinMode(pinoLed, OUTPUT); // Define o pino do LED como saída
  pinMode(vermelho, INPUT_PULLUP); // Define o pino do botão vermelho como entrada com pull-up
  pinMode(azul, INPUT_PULLUP); // Define o pino do botão azul como entrada com pull-up
  lcd.begin(16,2); // Inicializa o LCD com 16 colunas e 2 linhas
  Serial.begin(9600); // Inicializa a comunicação serial com taxa de transmissão de 9600 bps
}

// Função de contar o tempo
void timer() {
  lcd.clear(); // Limpa o LCD
  while(true){ // Loop infinito
    if(digitalRead(vermelho) == LOW){ // Se o botão vermelho for pressionado
      while(digitalRead(azul) == HIGH){ // Enquanto o botão azul não for pressionado
        lcd.setCursor(0,1); // Define a posição do cursor do LCD
        lcd.print("Azul = continuar"); // Exibe uma mensagem no LCD

        if(digitalRead(vermelho) == LOW){ // Se o botão vermelho for pressionado novamente
          while (digitalRead(azul) == HIGH){ // Enquanto o botão azul não for pressionado
            if (digitalRead(vermelho) == LOW && !botaoPressionado){ // Se o botão vermelho for pressionado e o botão não estiver sido previamente pressionado
              tempoInicio = millis(); // Armazena o tempo atual
              botaoPressionado = true; // Marca o botão como pressionado
            }

            if (digitalRead(vermelho) == HIGH && botaoPressionado){ // Se o botão vermelho for solto e o botão estiver pressionado
              unsigned long tempoPressionado = millis() - tempoInicio; // Calcula o tempo de pressionamento do botão
              Serial.print("O botao foi pressionado por "); // Exibe uma mensagem no monitor serial
              Serial.print(tempoPressionado); // Exibe o tempo de pressionamento
              Serial.println(" millisegundos"); // Exibe uma mensagem no monitor serial
              botaoPressionado = false; // Marca o botão como não pressionado
              if (tempoPressionado >= 3000){ // Se o botão foi pressionado por mais de 3 segundos
                return; // Sai da função
              }
            }
          }
        }
      }
      lcd.clear(); // Limpa o LCD
    }

    unsigned long temporizador = millis(); // Obtém o tempo atual em milissegundos

    if (temporizador - tempoAnterior >= intervalo){ // Se passou o intervalo de 1 segundo
      tempoAnterior = temporizador; // Atualiza o tempo anterior

      if(estadoLed == LOW){ // Se o LED está desligado
        estadoLed = HIGH; // Liga o LED
      }else {
        estadoLed = LOW; // Desliga o LED
      }

      digitalWrite(pinoLed, estadoLed); // Define o estado do LED

      // Incrementa os segundos e os minutos conforme necessário
      segundos++;
      if (segundos >= 60){
        segundos = 0;
        minutos++;
      }

      // Exibe o tempo no monitor serial
      if(segundos < 10){
        if(minutos < 10){
          Serial.print("Temporizador: ");
          Serial.print("0");
          Serial.print(minutos);
          Serial.print(":");
          Serial.print("0");
          Serial.println(segundos);
        } else {
          Serial.print("Temporizador: ");
          Serial.print(minutos);
          Serial.print(":");
          Serial.print("0");
          Serial.println(segundos);
        }
      } else {
        if (minutos < 10){
          Serial.print("Temporizador: ");
          Serial.print("0");
          Serial.print(minutos);
          Serial.print(":");
          Serial.println(segundos);
        } else {
          Serial.print("Temporizador: ");
          Serial.print(minutos);
          Serial.print(":");
          Serial.println(segundos);
        }
      }
      
      // Exibe o tempo no LCD
      if(segundos < 10){
        if(minutos < 10){
          lcd.setCursor(1,0);
          lcd.print("Tempo: ");
          lcd.setCursor(8,0);
          lcd.print("0");
          lcd.print(minutos);
          lcd.print(":");
          lcd.print("0");
          lcd.print(segundos);
          lcd.setCursor(1,1);
          lcd.print("Vermelho=pause");
        } else {
          lcd.setCursor(1,0);
          lcd.print("Tempo: ");
          lcd.setCursor(8,0);
          lcd.print(minutos);
          lcd.print(":");
          lcd.print("0");
          lcd.print(segundos);
          lcd.setCursor(1,1);
          lcd.print("Vermelho=pause");
        }
      } else {
        if (minutos < 10){
          lcd.setCursor(1,0);
          lcd.print("Tempo: ");
          lcd.setCursor(8,0);
          lcd.print("0");
          lcd.print(minutos);
          lcd.print(":");
          lcd.print(segundos);
          lcd.setCursor(1,1);
          lcd.print("Vermelho=pause");
        } else {
          lcd.setCursor(1,0);
          lcd.print("Tempo: ");
          lcd.setCursor(8,0);
          lcd.print(minutos);
          lcd.print(":");
          lcd.print(segundos);
          lcd.setCursor(1,1);
          lcd.print("Vermelho=pause");
        }
        
      }
    }
  }
}

void loop() {
  lcd.clear(); // Limpa o LCD
  segundos = 0; // Reinicia os segundos
  minutos = 0; // Reinicia os minutos
  if(digitalRead(azul) == LOW){ // Se o botão azul for pressionado
    Serial.println("Azul");
    timer(); // Chama a função timer
  } else {
    Serial.println("Nenhum botão");
    lcd.setCursor(3,0);
    lcd.print("Botao Azul =");
    lcd.setCursor(5,1);
    lcd.print("START");
  }

  delay(500); // Aguarda 500 milissegundos
}