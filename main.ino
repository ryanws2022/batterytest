#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Adafruit_SPIDevice.h>
#include <Adafruit_ADS1X15.h> /* Include la librairie utilisé */
Adafruit_ADS1115 ads;  /* Librairie pour la version 16 bit non utilisé ici */
/*Adafruit_ADS1015 ads; /* Librairie pour la version 12 bit */
 
void setup(void) /*Définit une fonction sans paramètre (void)*/
{

  pinMode(12, OUTPUT); //Led ROUGE
  pinMode(10, OUTPUT); //Led ORANGE
  pinMode(8, OUTPUT); //Led VERTE

  Serial.begin(9600); /*Définition du débit de données en bits par secondes pour transmettre des données.
                       Il faut que le contrôleur et l'ordi soit sur le même débit.*/
                       
  Serial.println("Salut !"); /* Imprime dans la console les messages entre "". Utilisé souvent pour du débug. */
  Serial.println("Getting single-ended readings from AIN0..3"); /* Obtenir des lectures asymétriques pour les ports AIN0-3 */
  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)"); /* Annonce dans la console que la valeur max est de 6.144V */
  
  
   ads.setGain(GAIN_TWOTHIRDS); // 2/3x gain +/- 6.144V 1 bit = 3mV 0.1875mV (default)
  // ads.setGain(GAIN_ONE); // 1x gain +/- 4.096V 1 bit = 2mV 0.125mV
  // ads.setGain(GAIN_TWO); // 2x gain +/- 2.048V 1 bit = 1mV 0.0625mV
  // ads.setGain(GAIN_FOUR); // 4x gain +/- 1.024V 1 bit = 0.5mV 0.03125mV
  // ads.setGain(GAIN_EIGHT); // 8x gain +/- 0.512V 1 bit = 0.25mV 0.015625mV
  // ads.setGain(GAIN_SIXTEEN); // 16x gain +/- 0.256V 1 bit = 0.125mV 0.0078125mV

/* Si ADS n'est pas initialisé, alors il écrit dans la console ce message pour débug". */
  
  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS."); 
    while (1);
  }
}

void loop(void)
{
  int16_t adc0, adc1, adc2, adc3; /* Changement à 16 bits */

/* Nombre à virgule flottante, nombre qui comporte une virgule décimale pour approximer des valeurs analogiques
car plus grade résolution. Possible d'afficher jusqu'à 3.4028235x10puissance38 */
  
  float volts0, volts1, volts2, volts3; 

/* Commande qui est l'opé réelle qui lance une mesure dans l'ADC avec entre () la variabel du canal (ou port) qui doit être mesurée. */
  
  adc0 = ads.readADC_SingleEnded(0); 
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);

/* Ces opérations sont la conversion des valeurs qui sont enregistrés en une tension */
  
  volts0 = ads.computeVolts(adc0);
  volts1 = ads.computeVolts(adc1);
  volts2 = ads.computeVolts(adc2);
  volts3 = ads.computeVolts(adc3);

  

/* C'est la sortie (ou impression) des valeurs (en V) de tous les canaux sur une interface (physique ou console) */
/* Serial.print() affiche uniquement des chiffres ou des variables... tandis que Serial.println() affiche une ligne de caractères "" */

Serial.println("-----------------------------------------------------------");
Serial.println(" ");
Serial.println(" ");
Serial.println(" ");
Serial.print("(Entrée A0) -> Valeur convertie (16b) : N="); Serial.print(adc0); Serial.print(" --- Tension (Volts) : "); Serial.print(volts0); Serial.println("V");
//Serial.print("(Entrée A1) -> Valeur convertie (16b) : N="); Serial.print(adc1); Serial.print(" --- Tension (Volts) : "); Serial.print(volts1); Serial.println("V");
//Serial.print("(Entrée A2) -> Valeur convertie (16b) : N="); Serial.print(adc2); Serial.print(" --- Tension (Volts) : "); Serial.print(volts2); Serial.println("V");
//Serial.print("(Entrée A3) -> Valeur convertie (16b) : N="); Serial.print(adc3); Serial.print(" --- Tension (Volts) : "); Serial.print(volts3); Serial.println("V");

//12v    = 5.41v converti   28821
//12.4v  = 5.43v converti     28929

//12.7 = 5.53  = 28950
//12.4= 5.48  = 28929

//5.78

//289996


if ((ads.readADC_SingleEnded(0)) < 28821) { //Ou 5.41V

    digitalWrite(10, LOW);
    digitalWrite(8, LOW);
    
  
    Serial.print("En dessous de 12V + LED. Rouge clignotante");
    digitalWrite(12, HIGH);
    delay(100);
    digitalWrite(12, LOW);
  
  } else if ((ads.readADC_SingleEnded(0)) >= 28929) { //Ou 5.43V
    digitalWrite(12, LOW);
    digitalWrite(10, LOW);
    
    Serial.print("Au dessus de 12.4V + LED. Verte");
    digitalWrite(8, HIGH);
  } else if ((ads.readADC_SingleEnded(0)) > 28821 && (ads.readADC_SingleEnded(0)) < 28929)  {

    digitalWrite(12, LOW);
    digitalWrite(8, LOW);
    
    Serial.print("Au dessus de 12V + LED. Orange");
    digitalWrite(10, HIGH);

  } else {
    
  }

Serial.println(" ");
Serial.println(" ");
Serial.println(" ");
 
  /* Délai avant boucle suivante */
  delay(1000); 
  
}
