#include <DHT.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x20,16,2);

#define DHTTYPE DHT11 
float lectura,voltage,temperatura,TempF,TempK,ValorLuz,Humedad;
const int A = 1000; 
const int B = 15;
const int Rc = 10;
int a = 0, ilum;
DHT dht(5,DHTTYPE);
  
void setup()
{
  attachInterrupt(0, intt, RISING); //PARA QUE OBSERVE DE FORMA INMEDIATA LOS CAMBIOS DEL PULSADO
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("TRABAJO DE");
  lcd.setCursor(2, 1);
  lcd.print("COMPUTACION.");
  delay(1000);
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("LA SALLE");
  lcd.setCursor(4,1);
  lcd.print("CORDOBA.");
  delay(1000);
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("ESTACION");
  lcd.setCursor(1,1);
  lcd.print("METEOROLOGICA.");
  delay(1000);
  lcd.clear();
}


void loop()
{
  //SENSOR DE TEMPERATURA
  
    
  lectura = analogRead(0); //Recoge la lectura del Sensor TMP36 del pin A0
  voltage = lectura * (5000 / 1024.0); //transforma la lectura en voltios
  temperatura = (voltage - 500) / 10; //pasa de voltages a temp según el factor de conversión del sensor
  
  //CONVERSIÓN DE TEMPERATURAS
  
  TempF= (temperatura * (9/5) + 32.0);
  TempK= (temperatura + 273.15);
  
  //MOSTRAR EN EL LCD
  
  switch (a) {
    case 0:
          lcd.setCursor(0,0);
          lcd.print("Grados C: ");
          lcd.print(temperatura);
          
		
          break;
    case 1:
          lcd.setCursor(0,0);
          lcd.print("Grados K:");
          lcd.print(TempK);
          
          break;
           //Puede haber los “case” que se deseen, y al final una sección default 
    case 2:
          lcd.setCursor(0,0);
          lcd.print("Grados F:");
          lcd.print(TempF);
         
          break;

      }

  //VALOR DE TEMPERATURA
  
  if (temperatura < 25) {
  		lcd.setCursor(9,1);
        lcd.print ("Temp B");
	} else if (temperatura > 35) {
  		lcd.setCursor(9,1);
        lcd.print ("Temp A");
	} else {
  		lcd.setCursor(9,1);
        lcd.print ("Temp M");
	}
  	
  
  
  //SENSOR DE LUMINOSIDAD EN LUX
  
  ValorLuz = analogRead(1);
  ilum = ((long)(1024-ValorLuz)*A*10)/((long)B*Rc*ValorLuz);
  lcd.setCursor(0,1);
  lcd.print("Lux:");
  lcd.print(ilum);
    
  //SENSOR DE HUMEDAD
  
  Humedad = dht.readHymidity();
  lcd.setCursor(0,1);
  lcd.print ("Hum:");
  lcd.print:
}

void intt() //LA INTERRUPCIÓN DEL PULSADOR
{

  a+=1;
  a%=3;

}

