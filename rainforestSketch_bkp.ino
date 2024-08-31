// REFERÊNCIAS:
//  Apostila Eletrogate - KIT MAKER 
//   Exemplo 13 – Arduino Sensor de umidade do solo e Sensor de chuva - Gustavo Murta

// Componentes físicos 
int sensorUmidadeSolo = A0;             // Sensor de umidade do solo pino A0 conectado no A0 do Arduino 
int sensorChuva = A1;                   // Sensor de chuva pino A1 conectado no A1 do Arduino 
int sensorTemperatura = A2;             // Sensor de chuva pino A2 conectado no A2 do Arduino 
int portaRele = 4;                      // porta de controle do relé conectada no D4 do Arduino 

// Parametros de controle do ecosistema
int valorLimiteUmidade = 500;           // valor da tensão de comparação do sensor / valor máximo = 1024 
int valorLimiteChuva = 500;             // valor da tensão de comparação do sensor / valor máximo = 1024  
int temperaturaAtual = 20;              // valor de tensão de comparação do sensor / valor máximo = Não sei / média esperada 20 graus

int tempoDeRegaInicial = 2000;          // em milisegundos
int taxaCrescimento = 0;                // em milisegundos
int taxaQueda = 0;                      // em milisegundos
int tempoDeRega = 3000;                 // em milisegundos
bool soloUmido;                         // condição de solo úmido
char clima = "normal";                  // normal: > 18 & < 22 graus celcius

 
void setup() { 
  pinMode(sensorUmidadeSolo, INPUT);     // Sensor de umidade do solo - porta A0 é entrada 
  pinMode(sensorChuva, INPUT);           // Sensor de chuva - porta A1 é entrada 
  pinMode(portaRele, OUTPUT);            // Porta de controle do Relé - D4 é saída 
  digitalWrite(portaRele, HIGH);         // Mantenha relé desligado  
  Serial.begin(9600);                    // Monitor console 9600 Bps 
} 

void SensorDeUmidade(int valorLimiteUmidade = 500) 
{ 
  int valorSensorUmidadeSolo = analogRead(sensorUmidadeSolo);    // leitura do Sensor de umidade do solo 
  Serial.print(" Sensor de umidade do solo = ");                 // imprime mensagem 
  Serial.print(valorSensorUmidadeSolo);                          // valor do sensor de umidade do solo 
  if (valorSensorUmidadeSolo < valorLimiteUmidade)               // se o valor for menor do que o limite 
  { 
    Serial.println("  => O solo esta úmido");                    // imprime a mensagem 
    soloUmido = 1 ;                                              // solo esta úmido  
  } 
  else                                                           // senão 
  { 
    Serial.println("  => O solo esta seco");                     // imprime a mensagem 
    soloUmido = 0 ;                                              // solo não esta úmido  
  } 
} 

void SensorDeTemperatura()
{ 
  int valorSensorTemperatura = analogRead(sensorTemperatura);    // leitura do Sensor de umidade do solo 
  Serial.print(" Sensor de temperatura = ");                     // imprime mensagem 
  Serial.print(valorSensorTemperatura);                          // valor do sensor de umidade do solo 
  if (valorSensorTemperatura < temperaturaMinima)                // se o valor for menor do que o limite 
  { 
    Serial.println("  => O clima esta frio");                    // imprime a mensagem 
    clima = "frio" ;                                              // solo esta úmido  
  } 
  else if (valorSensorTemperatura > temperaturaMáximab)                                                           // senão 
  { 
    Serial.println("  => O clima esta quente");                     // imprime a mensagem 
    clima = "quente" ;                                              // solo não esta úmido  
  }
  else
  {
    Serial.println("  => O clima está adequado");                     // imprime a mensagem 
    clima = "normal" ;                                              // solo não esta úmido  
  }
} 

void AcionarBombaDagua(int tempoDeRega = 3000)                  // ajuste o tempo de acionamento da bomba 
{
  int tempoEmSegundos = tempoDeRega / 1000
  digitalWrite(portaRele, HIGH);                                // relé desligado 
  Serial.println(F("Bomba d'água acionada por... "));           // imprime a mensagem 
  Serial.println(tempoEmSegundos + " segundos");             // imprime a mensagem 
  digitalWrite(portaRele, LOW);                                 // relé ligado 
  Serial.println(F("regando... "));                             // imprime a mensagem 
  delay (tempoDeRega);                                          // tempo de acionamento da bomba dágua = 3 segundo(s)
  digitalWrite(portaRele, HIGH);                                // relé desligado 
  Serial.println(F("bomba d'água desligada... "));              // imprime a mensagem 
} 

/* CONTROLE DE CHUVA */

void ChuvaCrescente(tempoDeRegaInicial, taxaCrescimento, intervaloPancadasDeChuva, qtdOcorrenciasChuva){
  tempoDeRega = tempoDeRegaInicial
  for (int i = 0; i < qtdOcorrenciasChuva; i++){   // repete pancadas de chuva de acordo com parametros acima
    AcionarBombaDagua(tempoDeRega)
    delay(intervaloPancadasDeChuva)
    tempoDeRega += taxaCrescimento                 // aumento do tempo de chuva
  }
}

void ChuvaDecrescente(tempoDeRegaInicial, taxaQueda, intervaloPancadasDeChuva, qtdOcorrenciasChuva){
  tempoDeRega = tempoDeRegaInicial
  for (int i = 0; i < qtdOcorrenciasChuva; i++){   // repete pancadas de chuva de acordo com parametros acima
    AcionarBombaDagua(tempoDeRega)
    delay(intervaloPancadasDeChuva)
    tempoDeRega -= taxaQueda                      // queda do tempo de chuva
  }
}

void ChuvaDeVerao(){                                                                                           // alta volumetria
  /* parammetros de volumetria alta */
  tempoDeRegaInicial = 3000                                                                                 // primeira pancada de chuva
  taxaCrescimento = 2500
  taxaQueda = 2500
  intervaloPancadasDeChuva = 5000
  qtdOcorrenciasChuva = 9
  qtdOcorrenciasChuvaCrescente = int(qtdOcorrenciasChuva / 2)                                                    // se qtdOcorrencias seleciona a metade arredondando pra cima
  qtdOcorrenciasChuvaDecrescente = qtdOcorrenciasChuva - qtdOcorrenciasChuvaCrescente

  /* comportamento Distribuição Normal - Gaussiana */
  ChuvaCrescente(tempoDeRegaInicial, taxaCrescimento, intervaloPancadasDeChuva, qtdOcorrenciasChuvaCrescente)
  delay(intervaloPancadasDeChuva)
  ChuvaDecrescente(tempoDeRega, taxaQueda, intervaloPancadasDeChuva, qtdOcorrenciasChuvaDecrescente)             // utiliza ultimo tempo de rega estabelecido e completa a quantidade de ocorrencia esperadas
}

void ChuvaNormal(){                                                                                           // volumetria média
  /* parammetros de volumetria média */
  tempoDeRegaInicial = 2000                                                                                      // primeira pancada de chuva
  taxaCrescimento = 2000
  taxaQueda = 2000
  intervaloPancadasDeChuva = 7000
  qtdOcorrenciasChuva = 7
  qtdOcorrenciasChuvaCrescente = int(qtdOcorrenciasChuva / 2)                                                    // se qtdOcorrencias seleciona a metade arredondando pra cima
  qtdOcorrenciasChuvaDecrescente = qtdOcorrenciasChuva - qtdOcorrenciasChuvaCrescente

  /* comportamento Distribuição Normal - Gaussiana */
  ChuvaCrescente(tempoDeRegaInicial, taxaCrescimento, intervaloPancadasDeChuva, qtdOcorrenciasChuvaCrescente)
  delay(intervaloPancadasDeChuva)
  ChuvaDecrescente(tempoDeRega, taxaQueda, intervaloPancadasDeChuva, qtdOcorrenciasChuvaDecrescente)             // utiliza ultimo tempo de rega estabelecido e completa a quantidade de ocorrencia esperadas
}


void ChuvaDeInverno(){                                                                                           // baixa volumetria
  /* parammetros de volumetria baixa */
  tempoDeRegaInicial = 1000                                                                                      // primeira pancada de chuva
  taxaCrescimento = 15000
  taxaQueda = 1500
  intervaloPancadasDeChuva = 9000
  qtdOcorrenciasChuva = 5
  qtdOcorrenciasChuvaCrescente = int(qtdOcorrenciasChuva / 2)                                                    // se qtdOcorrencias seleciona a metade arredondando pra cima
  qtdOcorrenciasChuvaDecrescente = qtdOcorrenciasChuva - qtdOcorrenciasChuvaCrescente

  /* comportamento Distribuição Normal - Gaussiana */
  ChuvaCrescente(tempoDeRegaInicial, taxaCrescimento, intervaloPancadasDeChuva, qtdOcorrenciasChuvaCrescente)
  delay(intervaloPancadasDeChuva)
  ChuvaDecrescente(tempoDeRega, taxaQueda, intervaloPancadasDeChuva, qtdOcorrenciasChuvaDecrescente)             // utiliza ultimo tempo de rega estabelecido e completa a quantidade de ocorrencia esperadas
}

/* CONTROLE DE VENTO */

void ventoCrescente(tempoDeRegaInicial, taxaCrescimento, intervaloPancadasDeChuva, qtdOcorrenciasChuva){
  tempoDeRega = tempoDeRegaInicial
  for (int i = 0; i < qtdOcorrenciasChuva; i++){   // repete pancadas de chuva de acordo com parametros acima
    AcionarBombaDagua(tempoDeRega)
    delay(intervaloPancadasDeChuva)
    tempoDeRega += taxaCrescimento                 // aumento do tempo de chuva
  }
}

void VentoDecrescente(tempoDeRegaInicial, taxaQueda, intervaloPancadasDeChuva, qtdOcorrenciasChuva){
  tempoDeRega = tempoDeRegaInicial
  for (int i = 0; i < qtdOcorrenciasChuva; i++){   // repete pancadas de chuva de acordo com parametros acima
    AcionarBombaDagua(tempoDeRega)
    delay(intervaloPancadasDeChuva)
    tempoDeRega -= taxaQueda                      // queda do tempo de chuva
  }
}

void VentoDeVerao(){                                                                                           // alta volumetria
  /* parammetros de volumetria alta */
  tempoDeRegaInicial = 3000                                                                                 // primeira pancada de chuva
  taxaCrescimento = 2500
  taxaQueda = 2500
  intervaloPancadasDeChuva = 5000
  qtdOcorrenciasChuva = 9
  qtdOcorrenciasChuvaCrescente = int(qtdOcorrenciasChuva / 2)                                                    // se qtdOcorrencias seleciona a metade arredondando pra cima
  qtdOcorrenciasChuvaDecrescente = qtdOcorrenciasChuva - qtdOcorrenciasChuvaCrescente

  /* comportamento Distribuição Normal - Gaussiana */
  ChuvaCrescente(tempoDeRegaInicial, taxaCrescimento, intervaloPancadasDeChuva, qtdOcorrenciasChuvaCrescente)
  delay(intervaloPancadasDeChuva)
  ChuvaDecrescente(tempoDeRega, taxaQueda, intervaloPancadasDeChuva, qtdOcorrenciasChuvaDecrescente)             // utiliza ultimo tempo de rega estabelecido e completa a quantidade de ocorrencia esperadas
}

void VentoNormal(){                                                                                           // volumetria média
  /* parammetros de volumetria média */
  tempoDeRegaInicial = 2000                                                                                      // primeira pancada de chuva
  taxaCrescimento = 2000
  taxaQueda = 2000
  intervaloPancadasDeChuva = 7000
  qtdOcorrenciasChuva = 7
  qtdOcorrenciasChuvaCrescente = int(qtdOcorrenciasChuva / 2)                                                    // se qtdOcorrencias seleciona a metade arredondando pra cima
  qtdOcorrenciasChuvaDecrescente = qtdOcorrenciasChuva - qtdOcorrenciasChuvaCrescente

  /* comportamento Distribuição Normal - Gaussiana */
  ChuvaCrescente(tempoDeRegaInicial, taxaCrescimento, intervaloPancadasDeChuva, qtdOcorrenciasChuvaCrescente)
  delay(intervaloPancadasDeChuva)
  ChuvaDecrescente(tempoDeRega, taxaQueda, intervaloPancadasDeChuva, qtdOcorrenciasChuvaDecrescente)             // utiliza ultimo tempo de rega estabelecido e completa a quantidade de ocorrencia esperadas
}


void VentoDeInverno(){                                                                                           // baixa volumetria
  /* parammetros de volumetria baixa */
  tempoDeRegaInicial = 1000                                                                                      // primeira pancada de chuva
  taxaCrescimento = 15000
  taxaQueda = 1500
  intervaloPancadasDeChuva = 9000
  qtdOcorrenciasChuva = 5
  qtdOcorrenciasChuvaCrescente = int(qtdOcorrenciasChuva / 2)                                                    // se qtdOcorrencias seleciona a metade arredondando pra cima
  qtdOcorrenciasChuvaDecrescente = qtdOcorrenciasChuva - qtdOcorrenciasChuvaCrescente

  /* comportamento Distribuição Normal - Gaussiana */
  ChuvaCrescente(tempoDeRegaInicial, taxaCrescimento, intervaloPancadasDeChuva, qtdOcorrenciasChuvaCrescente)
  delay(intervaloPancadasDeChuva)
  ChuvaDecrescente(tempoDeRega, taxaQueda, intervaloPancadasDeChuva, qtdOcorrenciasChuvaDecrescente)             // utiliza ultimo tempo de rega estabelecido e completa a quantidade de ocorrencia esperadas
}



void SensorDeTemperatura(){

}

void loop() 
{

  /* INDICES CLIMÁTICOS EM FLORESTAS
  - Temperatura média de 20 graus Célcius
  - Chove de 3 a 6 milímetros por ano
  - Menos chuva no inverno
  - Mais chuva no verão
  */

  SensorDeUmidade (valorLimiteUmidade);         // faz medição do sensor de umidade do solo
  SensorDeTemperatura ();                       // faz medição do sensor de umidade do solo

  switch (clima) {
    case "quente":                              // acima de 22 graus celcius
      ChuvaDeVerao()                            // determina a volumetria de chuva
      VentoDeVerao()                            // determina a frequencia de rajadas de vento
  w    break;
    case "frio":                                // abaixo de 18 graus celcius
      ChuvaDeInverno()                          // determina a volumetria de chuva
      VentoDeInverno()                          // determina a frequencia de rajadas de vento
      break;
    default:                                    // média esperada de 20 graus celcius
      ChuvaNormal()                             // determina a volumetria de chuva
      VentoNormal()                             // determina a frequencia de rajadas de vento
      break;
  }
} 