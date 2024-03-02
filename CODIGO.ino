#include <DHT.h>
#include <DHT_U.h>




#include <LiquidCrystal.h>

DHT dht(3, DHT11);

const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int Humedad_del_Suelo = A0;

const int Relay_Bomba = 12;
const int Relay_Ventilador = 13;

void setup()
{

  dht.begin();

  Serial.begin(9600);

  lcd.begin(16, 2);

  pinMode(Humedad_del_Suelo, INPUT);
  pinMode(Relay_Bomba, OUTPUT);
  pinMode(Relay_Ventilador, OUTPUT);
}

void loop()
{

  if (Serial.available() > 0)
  {
    int entrada = Serial.read();
    switch (entrada)
    {
    case '0':
      digitalWrite(12, HIGH);
      lcd.print("Riego ON");
      break;

    case '1':
      digitalWrite(13, HIGH);
      lcd.print("Ventilacion ON");
      break;
   
    case '2':
      digitalWrite(12, LOW);
      lcd.print("Riego OFF");
      break;

    case '3':
      digitalWrite(13, LOW);
      lcd.print("Ventilacion OFF");
      break;
   
    default:
      break;
    }
  }
  float Temperature = dht.readTemperature();
  float Humidity = dht.readHumidity();
  float Valor_Humedad = analogRead(Humedad_del_Suelo);

  Serial.print(Temperature, " C,");
  Serial.print(Humidity, " %,");
  Serial.print(Valor_Humedad/ 10, " %,");
  Serial.println();

  Mostrar(lcd, Temperature, Humidity, Valor_Humedad);
  Riego(Valor_Humedad, lcd, Relay_Bomba);
  ventilacion(Temperature, Relay_Ventilador, lcd);
}

void Riego(float Valor, LiquidCrystal lcd, const int Relay_Bomba)
{
  if (Valor <= 300)
  {
    digitalWrite(Relay_Bomba, HIGH);
    lcd.print("Bomba Activada");
    delay(5000);
    
    lcd.clear();
  }
  else
  {
    digitalWrite(Relay_Bomba, LOW);
    lcd.print("Bomba Apagada");
    delay(1000);
    
    lcd.clear();
  }
}

void ventilacion(float temperatura, const int Relay_Ventilador, LiquidCrystal lcd)
{
  if (temperatura > 30)
  {
    digitalWrite(Relay_Ventilador, HIGH);
    lcd.print("Ventilacion ON");
    delay(2000);
    
    lcd.clear();

  }
  else
  {
    digitalWrite(Relay_Ventilador, LOW);
    lcd.print("Ventilacion OFF");
    delay(1000);
    
    lcd.clear();

  }
}

void Mostrar(LiquidCrystal lcd, float Temperature, float Humidity, float Valor_Humedad)
{
  lcd.print("Bienvenidos a la");
  lcd.setCursor(0, 1);
  lcd.print("Casa de Cultivos");
  delay(1000);
 
  lcd.clear();
  delay(1000);
 
  lcd.print("Temp: " + String(Temperature) + " C");
  lcd.setCursor(0, 1);
  lcd.print("Humd: " + String(Humidity) + "%");
  delay(1000);
 
  lcd.clear();
  delay(1000);
  
  lcd.print("Humedad Suelo");
  lcd.setCursor(0, 1);
  lcd.print(String(Valor_Humedad / 10) + "%");
  delay(1000);
 
  lcd.clear();
  delay(1000);
}