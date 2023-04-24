#include <DHT.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

#define DHTPIN 5
#define DHTTYPE DHT11
float lectura,voltage,temperatura,TempF,TempK,ValorLuz;
const int A = 1000; 
const int B = 15;
const int Rc = 10;
int a = 0, j = 0, ilum, Humedad, anterior;
DHT dht(5,DHTTYPE);
  
void setup()
{
  attachInterrupt(0, intt, RISING); //PARA QUE OBSERVE DE FORMA INMEDIATA LOS CAMBIOS DEL PULSADO
  attachInterrupt(1, intt2, RISING);
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("TRABAJO DE");
  lcd.setCursor(2, 1);
  lcd.print("COMPUTACION.");
  delay(2000);
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("LA SALLE");
  lcd.setCursor(4,1);
  lcd.print("CORDOBA.");
  delay(2000);
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("ESTACION");
  lcd.setCursor(1,1);
  lcd.print("METEOROLOGICA.");
  delay(2000);
  lcd.clear();
}


void loop()
{
  static unsigned long TiempoAnteriorT = 0;
  const unsigned long intervaloT = 2000;
  static unsigned long lastChangeTime = 0; 
  const unsigned long intervalo = 10000; 
  static int estado = 0; 

  if (millis() - lastChangeTime >= intervalo) 
  {
    estado = (estado + 1) % 2; 
    lastChangeTime = millis(); 
  }
  
  if (millis() - TiempoAnteriorT >= intervaloT) {  // Comprueba si ha pasado el intervalo deseado desde la última lectura
    lectura = analogRead(0); //Recoge la lectura del Sensor TMP36 del pin A0
    voltage = lectura * (5000 / 1024.0); //transforma la lectura en voltios
    temperatura = (voltage - 500) / 10; //pasa de voltages a temp según el factor de conversión del sensor
    TiempoAnteriorT = millis();  // Almacena el tiempo actual como el tiempo anterior para la próxima comparación
  }

  //MOSTRAR EN EL LCD
  switch (j) {

    case 0:
      switch (a) 
      {
        case 0:
          lcd.setCursor(0,0);
          lcd.print("Grados C: ");
          lcd.print(temperatura);
        
          break;
        case 1:
          TempK= (temperatura + 273.15);
          lcd.setCursor(0,0);
          lcd.print("Grados K:");
          lcd.print(TempK);
          
          break;
           //Puede haber los “case” que se deseen, y al final una sección default 
        case 2:
          TempF= (temperatura * (9/5) + 32.0);
          lcd.setCursor(0,0);
          lcd.print("Grados F:");
          lcd.print(TempF);
          
          break;
      }
    break;
    
    case 1:
      
      float SensacionTermica=dht.computeHeatIndex(temperatura, Humedad, false);
      lcd.setCursor(0,0);
      lcd.print ("Sen Term: ");
      lcd.print (SensacionTermica);
      lcd.print (" ");

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
  
  switch (estado) {
    case 0:
         //SENSOR DE LUMINOSIDAD EN LUX
          if (estado!=anterior) {
            lcd.setCursor(0,1);
            lcd.print("         ");
        }
          ValorLuz = analogRead(1);
          ilum = ((long)(1024-ValorLuz)*A*10)/((long)B*Rc*ValorLuz);
          lcd.setCursor(0,1);
          lcd.print("Lux:");
          lcd.print(ilum);
          delay(1000);
          break;
    case 1:
          //SENSOR DE HUMEDAD
          if (estado!=anterior) {
            lcd.setCursor(0,1);
            lcd.print("         ");
        }
          Humedad = dht.readHumidity();
          lcd.setCursor(0,1);
          lcd.print ("Hum:");
          lcd.print(Humedad);
          lcd.print("%");
          break;  

    }
  
  anterior = estado;
  
  
}

void intt() //LA INTERRUPCIÓN DEL PULSADOR
{
  a+=1;
  a%=3;
}
void intt2() //LA INTERRUPCIÓN DEL PULSADOR
{
  if (j==0)
  {
    j=1;
  }
    else
  {
    j=0;
  } 
}