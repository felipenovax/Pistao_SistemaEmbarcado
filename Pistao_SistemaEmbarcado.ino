/*

  Conexões do IBT-2:
  pino 1 do IBT-2 (RPWM) para pino 5 do arduino(PWM)
  pino 2 do IBT-2 (LPWM) para pino 6 do arduino(PWM)
  pinos 3 do IBT-2 (R_EN), 4 (L_EN), 7 (VCC) para pino 5v do arduino
  pino 8 do IBT-2 (GND) para GND do Arduino
  pinos 5 do IBT-2 (R_IS) e 6 (L_IS) não conectados

  outra placa segue o mesmo modelo de cima porem:
  pino 1 do IBT-2 (RPWM) para pino 9 do arduino(PWM)
  pino 2 do IBT-2 (LPWM) para pino 10 do arduino(PWM)
*/

bool ligadoA = false;
bool ligadoB = false;

const int ledPin = 13;
const int buttonpin2 = 2; //pra frente
const int buttonpin4 = 4; //pra tras

const int buttonpin7 = 7; //Motor A
const int buttonpin8 = 8; //Motor B

const int buttonpin3 = 3; //Bot�o Off
const int buttonpin11 = 11; //Bot�o On

const int LedA = A1;
const int LedB = A0;
const int LedOn = A2;

int botaoFrente = 0;
int botaoTras = 0;
int MotorA = 0;
int MotorB = 0;
int BotaoOff = 0;
int BotaoOn = 0;

int modificador = 0;
int marcador = 0;
int valor = 0;


int RPWM_A_Output = 5; // sa�da Arduino PWM pino 5; conectado no IBT-2 pino 1 (RPWM)
int LPWM_A_Output = 6; // sa�da Arduino PWM pino 6; conectado no IBT-2 pino 2 (LPWM)

int RPWM_B_Output = 9; // sa�da Arduino PWM pino 9; conectado no IBT-2 pino 1 (LPWM)
int LPWM_B_Output = 10; // sa�da Arduino PWM pino 10; conectado no IBT-2 pino 2 (LPWM)

unsigned int contador = 0;

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(LedA, OUTPUT);
  pinMode(LedB, OUTPUT);
  pinMode(LedOn, OUTPUT);
  pinMode(buttonpin2, INPUT);
  pinMode(buttonpin3, INPUT);
  
  // Placa A
  pinMode(RPWM_A_Output, OUTPUT);
  pinMode(LPWM_A_Output, OUTPUT);

  // Placa B
  pinMode(RPWM_B_Output, OUTPUT);
  pinMode(LPWM_B_Output, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  valor = marcador;
  valor = constrain(valor, 0, 1100);
  
  botaoFrente = digitalRead(buttonpin2);
  botaoTras = digitalRead(buttonpin4);
  MotorA = digitalRead(buttonpin7);
  MotorB = digitalRead(buttonpin8);
  BotaoOff = digitalRead(buttonpin3);
  BotaoOn = digitalRead(buttonpin11);
  
  // ZERA VALORES 
  
  if (botaoFrente == LOW && botaoTras == LOW && MotorA == LOW && MotorB == LOW)
  {
    // zera valores

    digitalWrite(ledPin, LOW);

    analogWrite(LPWM_A_Output, 0);
    analogWrite(RPWM_A_Output, 0);
    analogWrite(LPWM_B_Output, 0);
    analogWrite(RPWM_B_Output, 0);
  }

    
  // ********************************************************* FRENTE E TRAS MOTOR B
  
  else if(botaoFrente ==  HIGH && modificador == 0)
  {
  // rota��o pra frente
  digitalWrite(ledPin, HIGH);
  
    analogWrite(LPWM_A_Output, 0);
    analogWrite(RPWM_A_Output, 254);

    botaoFrente = LOW;
    marcador++;
    Serial.println(marcador);
    digitalWrite(ledPin, LOW);
  }
  
  else if(botaoTras == HIGH && modificador == 0)
  {
  // rota��o pra tras
    digitalWrite(ledPin, HIGH);

    analogWrite(LPWM_A_Output, 254);
    analogWrite(RPWM_A_Output, 0);

    botaoTras = LOW;
    marcador--;
    Serial.println(marcador);
    digitalWrite(ledPin, LOW);
  }
  
  // ********************************************************* FRENTE E TRAS MOTOR B
  
  else if(botaoFrente ==  HIGH && modificador == 1)
  {
  // rota��o pra frente
  digitalWrite(ledPin, HIGH);
  
    analogWrite(LPWM_B_Output, 0);
    analogWrite(RPWM_B_Output, 254);

    botaoFrente = LOW;
    marcador++;
    Serial.println(marcador);
    digitalWrite(ledPin, LOW);
  }
  
  else if(botaoTras == HIGH && modificador == 1)
  {
  // rota��o pra tras
    digitalWrite(ledPin, HIGH);

    analogWrite(LPWM_B_Output, 254);
    analogWrite(RPWM_B_Output, 0);

    botaoTras = LOW;
    marcador--;
    Serial.println(marcador);
    digitalWrite(ledPin, LOW);
  }
  
  // ********************************************************* LIGAR MOTOR A E RECUAR MOTOR B
  
  else if (MotorA == HIGH)
  {
    digitalWrite(LedA, HIGH);
    digitalWrite(LedB, LOW);
  digitalWrite(LedOn, LOW);

    for (int x = 0; x < 1100; x++)
    {


      // rota��o pra frente

      analogWrite(LPWM_A_Output, 0);
      analogWrite(RPWM_A_Output, 254);

      // rota��o pra tras

      analogWrite(LPWM_B_Output, 254);
      analogWrite(RPWM_B_Output, 0);
      contador++;
      Serial.println(contador);

    }

    ligadoA = true;
    ligadoB = false;
    modificador = 0;
    

  }
  
  
  // ********************************************************* LIGAR MOTOR B E RECUAR MOTOR A
  
  else if (MotorB == HIGH)
  {
    digitalWrite(LedB, HIGH);
    digitalWrite(LedA, LOW);
  digitalWrite(LedOn, LOW);
    
    for (int y = 0; y < 1100; y++)
    {

      // rota��o pra frente

      analogWrite(LPWM_B_Output, 0);
      analogWrite(RPWM_B_Output, 254);

      // rota��o pra tras

      analogWrite(LPWM_A_Output, 254);
      analogWrite(RPWM_A_Output, 0);
      contador++;
      Serial.println(contador);


    }


    ligadoB = true;
    ligadoA = false;
    modificador = 1;
    
  }
  
  // ********************************************************* BOTAO DESLIGAR MOTORES
  if (BotaoOff == HIGH)
  {
  digitalWrite(LedOn, LOW);
  digitalWrite(LedA, LOW);
  digitalWrite(LedB, LOW);
  
    if (ligadoA == true && ligadoB == true)
    {
      for (int x = 0; x < 1100; x++)
      {
        
    // rotação pra tras 
    
    analogWrite(LPWM_B_Output, 254);
        analogWrite(RPWM_B_Output, 0);
        analogWrite(LPWM_A_Output, 254);
        analogWrite(RPWM_A_Output, 0);
    contador++;
        Serial.println(contador);
    
      }
      ligadoA = false;
      ligadoB = false;
    }

    else if (ligadoA == true)
    {
      for (int x = 0; x < 1100; x++)
      {

        // rota��o pra tras
    

        analogWrite(LPWM_A_Output, 254);
        analogWrite(RPWM_A_Output, 0);
        contador++;
        Serial.println(contador);
      }
      ligadoA = false;
    }

    else if (ligadoB == true)
    {
      for (int x = 0; x < 1100; x++)
      {

       // rota��o pra tras

     
        analogWrite(LPWM_B_Output, 254);
        analogWrite(RPWM_B_Output, 0);
        contador++;
        Serial.println(contador);

      }
      ligadoB = false;

    }
  else
  {
    modificador = 0;
    Serial.println("desligado");
  }

    modificador = 0;
    
   
  } 
  
  // ********************************************************* BOTAO LIGAR TODOS OS MOTORES
  
  if (BotaoOn == HIGH)
  {
    digitalWrite(LedOn, HIGH);
    digitalWrite(LedA, HIGH);
    digitalWrite(LedB, HIGH);

    if (ligadoA == false && ligadoB == false)
    {
      for (int x = 0; x < 1100; x++)
      {

        // rota��o pra frente

        analogWrite(LPWM_A_Output, 0);
        analogWrite(RPWM_A_Output, 254);
        analogWrite(LPWM_B_Output, 0);
        analogWrite(RPWM_B_Output, 254);
        contador++;
        Serial.println(contador);

      }
      ligadoA = true;
      ligadoB = true;
    }

    else if (ligadoA == false)
    {
      for (int x = 0; x < 1100; x++)
      {

        // rotação pra frente


        analogWrite(LPWM_A_Output, 0);
        analogWrite(RPWM_A_Output, 254);
        contador++;
        Serial.println(contador);

      }
      ligadoA = true;
    }

    else if (ligadoB == false)
    {
      for (int x = 0; x < 1100; x++)
      {

        // rota��o pra frente


        analogWrite(LPWM_B_Output, 0);
        analogWrite(RPWM_B_Output, 254);
        contador++;
        Serial.println(contador);

      }
      ligadoB = true;
    }


    digitalWrite(ledPin, LOW);
    modificador = 0;
    //ligado = true;
  /*Serial.println(ligado);
  Serial.println(ligadoA);
  Serial.println(ligadoB);*/
  }
  
}
