const int pinoDegrau = 8;
const int pinoLeitura = A0;

void setup() {
  Serial.begin(115200);
  pinMode(pinoDegrau, OUTPUT);
  digitalWrite(pinoDegrau, LOW);

  // Prescaler do ADC em 16 
  ADCSRA = (ADCSRA & 0xF8) | 0x04;
}

void loop() {
  // Varredura de 0 a 100 microssegundos
  for (int atraso_us = 0; atraso_us <= 100; atraso_us += 2) { 
    
    // Aguarda 2 ms para descarregar capacitor
    digitalWrite(pinoDegrau, LOW); 
    delay(2); 

    // Degrau no pino 8 
    digitalWrite(pinoDegrau, HIGH); 
    
    delayMicroseconds(atraso_us); 
    
    // Tensão no capacitor
    int leitura = analogRead(pinoLeitura); 
    float v_real = leitura * (5.0 / 1023.0);
    
    // Escalonamento para a referência de 4.0V (0.8 = 4.0 / 5.0)
    float v_capacitor_4v = v_real * 0.8;
    float v_degrau_4v = 4.0; 

    // Plotadora Serial
    Serial.print("Degrau_Entrada:");
    Serial.print(v_degrau_4v);
    Serial.print(",");
    Serial.print("Resposta_RLC:");
    Serial.println(v_capacitor_4v);
  }
  
  Serial.println(); 
  
  delay(0.2); 
}