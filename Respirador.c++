/* C++ code

Requisitos:

*Deverá ter 2 LEDS, um vermelho e um verde.

*Deverá ter 4 botões: 
1 para ligar (acende LED verde e aciona o motor), 
1 para desligar (acende LED vermelho e para tudo), 
1 botão aumenta a velocidade do servomotor e 
1 botão diminui a velocidade.

*O servomotor deverá ficar em loop indo do menor ao maior ângulo e voltando simulando a respiração de uma pessoa.

*Quando o servomotor ao chegar na posição máxima deverá mitir um BIP grave

*Quando o servomotor ao chegar na posição mínima deverá emitir um outro BIP agudo */


#include <Servo.h> // inclui a biblioteca para servos motores

int LEDvermelho = 13; // LED vermelo
int LEDverde = 12; // LED verde
int Buzzer = 7; // Buzzer
int BotaoLigar = 11; // Botão para ligar o respirador
int BotaoDesligar = 10; // Botão para desligar o respirador
int BotaoMaisVel = 9; // Botão para aumentar a velocidade do respirador
int BotaoMenosVel = 8; // Botão para diminuir a velocidade do respirador
bool stateLigado = false;
int velocidadeRespirador = 1500;
  
Servo servo; // cria um objeto para controle do servo

void setup()
{
  pinMode(LEDvermelho, OUTPUT);
  pinMode(LEDverde, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(BotaoLigar, INPUT);
  pinMode(BotaoDesligar, INPUT);
  pinMode(BotaoMaisVel, INPUT);
  pinMode(BotaoMenosVel, INPUT);
  
  servo.attach(6);
 
  Serial.begin(9600);
}

void loop()
{
  if(digitalRead(BotaoLigar) == HIGH){
    stateLigado = true;
    digitalWrite(LEDverde, HIGH);
    digitalWrite(LEDvermelho, LOW);
    delay(200);
    Serial.print("Delay do servo: ");
    Serial.println(velocidadeRespirador);
}
  while(stateLigado == true){
    if(digitalRead(BotaoDesligar) == HIGH){
      stateLigado = false;
      digitalWrite(LEDvermelho, HIGH);
      digitalWrite(LEDverde, LOW);
      break;
    }
    if(digitalRead(BotaoMaisVel) == HIGH && velocidadeRespirador > 1000){
      velocidadeRespirador -= 500;
      Serial.print("Delay do servo: ");
      Serial.println(velocidadeRespirador);
    }
    if(digitalRead(BotaoMenosVel) == HIGH){
      velocidadeRespirador += 500;
      Serial.print("Delay do servo: ");
      Serial.println(velocidadeRespirador);
    }
    servo.write(180);
    delay(velocidadeRespirador);
    tone(Buzzer,100,100);
    servo.write(0);
    delay(velocidadeRespirador);
    tone(Buzzer, 3000, 100);
  }
}