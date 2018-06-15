#include <NewPing.h>
 
/*pines para sensores*/
#define TRIGGER_PIN_1  13 //sensor 1
#define ECHO_PIN_1     12 //sensor 1
#define TRIGGER_PIN_2  2 //sensor 2
#define ECHO_PIN_2     1 //sensor 2
#define MAX_DISTANCE 400
#include <SoftwareSerial.h>
SoftwareSerial BTserial(15, 14); // RX | TX 
/*Crear el objeto de la clase NewPing*/
NewPing sonar1(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE);
NewPing sonar2(TRIGGER_PIN_2, ECHO_PIN_2, MAX_DISTANCE);

/*pines para las luces*/
int greenled1 = 22;
int greenled2 = 23;
int greenled3 = 24;
int greenled4 = 25;
int orangeled1 = 26;
int orangeled2 = 27;
int yellowled1 = 28;
int yellowled2= 29;
int redled1 = 30;
int redled2 = 31;
int luzprincipal1 = 2;
int luzprincipal2 = 3;

int IN1= 8;
int IN2=7;

/*pin para el buzzer*/
int speakerPin = 11;

/*pin para el motor*/



int estado1 = 1;
int estado2 = 2;


int encendido_luz;
int intensidad_luz;
int distancia_1;
int distancia_2;
int alarma_on;
int encendido_apertura=1;
int intensidad_apertura=3;


void setup() {
  Serial.begin(9600);
  pinMode(greenled1, OUTPUT);
  pinMode(greenled2, OUTPUT);
  pinMode(greenled3, OUTPUT);
  pinMode(greenled4, OUTPUT);
  pinMode(orangeled1, OUTPUT);
  pinMode(orangeled2, OUTPUT);
  pinMode(yellowled1, OUTPUT);
  pinMode(yellowled2, OUTPUT);
  pinMode(redled1, OUTPUT);
  pinMode(redled2, OUTPUT);
  pinMode(luzprincipal1, OUTPUT);
  pinMode(luzprincipal2, OUTPUT);
  pinMode(speakerPin,OUTPUT);
  pinMode(estado1, INPUT);
  pinMode(estado2,INPUT);
  //Serial.println("que desdea hacer a-abrir b- luz c- parquear");

  pinMode (IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
    
  // HC-05 default serial speed for commincation mode is 9600
    BTserial.begin(9600);

}  
int Estado=0;
int var_parqueo=0;
char c;
int cont;
int encendido;
int intensidad;
void loop() {
    switch (Estado){//00 Control luz cochera-- 01 Apertura portón-- 10 Alarma-- 11 Definir default  
       case 0: //Estado cero, se controla el encendido y la intensidad de la luz principal
            Serial.println("Opciones de sus sistema: \n");
            Serial.println("Presione 1  para estacionar \n");
            Serial.println("Presione 4 para cambiar la intensidad");
            Estado = 10;
            break;
       case 10:
            recive();
            break;
        
        case 1: //Apertura de porton
          apertura_porton();
          delay(1000);
          Detener_porton();
          Estado = 11;
        break;
        
        case 2: // Cierre porton
        cierre_porton();
        delay(1000);
        Detener_porton();
        Estado = 0;
        break;

        case 11:
        Serial.println("Cuando termine de parquear presione a \n");
        Estado = 3;
        break;
            
        case 3: //Estado tres, parqueo del vehiculo, se mide la distancia y se avisa al usuario con leds y sonido
        recive();
        //Serial.println(Estado);
        if (Estado != 49){
        distancia_1=sensor1();
        sonido_distancia(distancia_1);
        control_leds(distancia_1,c);
        Estado = 3;  
        }
        else if (Estado == 49){
          Serial.println("Se estaciono correctamente \n");
          Estado = 2;
        }
        break;

        case 4:
        Serial.println("Intensidad de luz deseada entre 1 2 3 y nada para apagar");
        delay(4000);
        encendido = 1;
        recive();
        Serial.println(Estado);
        intensidad = Estado;
        control_luz_principal(encendido,intensidad);
        Estado = 0;
        break;
        
        
        case 5: //Estado cuatro, se notifica movimiento en la cochera
        Serial.println("estado4 \n");
          //distancia_1=sensor1();
          //distancia_2=sensor2();
          //alarma_on=deteccion_movimiento(distancia_1,distancia_2);
          //sonido_alarma(alarma_on);
          Estado = 0;
        break;
    }

}

char recive(){
    // Keep reading from HC-05 and send to Arduino Serial Monitor
    if (BTserial.available())
    {  
        c = BTserial.read();
       // Serial.write(c);
        Estado = c;
        return Estado;
    }
 
    // Keep reading from Arduino Serial Monitor and send to HC-05
    if (Serial.available())
    {   
        c =  Serial.read();
        //BTserial.write(c);  
        //Serial.println(c);
        Estado = int(c)-48;
       // Serial.print(Estado);
        return Estado;
    }
}

//Control del sensor de distancia uno
int sensor1(){
     // Esperar 1 segundo entre mediciones
  delay(100);
  // Obtener medicion de tiempo de viaje del sonido y guardar en variable uS
  int uS = sonar1.ping_median();
  int distancia = (uS / US_ROUNDTRIP_CM);
  // Imprimir la distancia medida a la consola serial
  //Serial.print("Distancia: ");
  // Calcular la distancia con base en una constante
  //Serial.print(uS / US_ROUNDTRIP_CM);
  //Serial.println("cm");
  return distancia;
}
//Control del sensor de distancia dos
int sensor2(){
     // Esperar 1 segundo entre mediciones
  delay(300);
  // Obtener medicion de tiempo de viaje del sonido y guardar en variable uS
  int uS = sonar2.ping_median();
  int distancia = (uS / US_ROUNDTRIP_CM);
  // Imprimir la distancia medida a la consola serial
  //Serial.print("Distancia: ");
  // Calcular la distancia con base en una constante
  //Serial.print(uS / US_ROUNDTRIP_CM);
  //Serial.println("cm");
  return distancia;
}

//Controla el encendido y la intensidad de la luz de la cochera (3 posible intensidades)
void control_luz_principal(int encendido, int intensidad){
   if(encendido!=0){
      if (intensidad == 1){
          analogWrite(luzprincipal1,300);
          analogWrite(luzprincipal2,300);
          return;
      }
      else if(intensidad == 2){
          analogWrite(luzprincipal1,150);
          analogWrite(luzprincipal2,150);
          return;
      }
      else if(intensidad == 3){
          analogWrite(luzprincipal1,50);
          analogWrite(luzprincipal2,50);
          return;
      }
      else{
        analogWrite(luzprincipal1,0);
        analogWrite(luzprincipal2,0);
        return;}
   }
 }
 
//Control del motor para la apertura del portón
void apertura_porton(){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  return;
  }
void cierre_porton(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  return;
  }
void Detener_porton(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
}
//Deteccción de obstaculos en la cochera
void deteccion_obstaculos(int distancia1, int distancia2){
  }

//Detección de movimiento en la cochera
int deteccion_movimiento(int distancia1, int distancia2){
  }
  
//Genera un bip para avisar que la distancia a la pared es menor al minimo establecido
void sonido_distancia(int distancia){
    if (distancia < 18){
    digitalWrite(speakerPin, HIGH);
    delay(50);
    digitalWrite(speakerPin, LOW);
    delay(10);
    }
    else{
    digitalWrite(speakerPin, LOW);
    }
  }

//Genera el sonido de una sirena para avisar que hay un intruso
void sonido_alarma(int alerta){
}




//Función para prender los leds de acuerdo a la distancia entre el auto y la pared
int control_leds(int distancia, char Estado){
    if(distancia<18){
    digitalWrite(greenled1, HIGH);
    digitalWrite(greenled2, HIGH);
    digitalWrite(greenled3, HIGH);
    digitalWrite(greenled4, HIGH);
    digitalWrite(orangeled1, HIGH);
    digitalWrite(orangeled2, HIGH);
    digitalWrite(yellowled1, HIGH);
    digitalWrite(yellowled2, HIGH);
    digitalWrite(redled1, HIGH);
    digitalWrite(redled2, HIGH);
    delay (300);
    digitalWrite(greenled1, LOW);
    digitalWrite(greenled2, LOW);
    digitalWrite(greenled3, LOW);
    digitalWrite(greenled4, LOW);
    digitalWrite(orangeled1, LOW);
    digitalWrite(orangeled2, LOW);
    digitalWrite(yellowled1, LOW);
    digitalWrite(yellowled2, LOW);
    digitalWrite(redled1, LOW);
    digitalWrite(redled2, LOW);
    delay (300);
    Estado =3;
    return Estado;
    }
  else if(distancia<20){
    digitalWrite(greenled1, HIGH);
    digitalWrite(greenled2, HIGH);
    digitalWrite(greenled3, HIGH);
    digitalWrite(greenled4, HIGH);
    digitalWrite(orangeled1, HIGH);
    digitalWrite(orangeled2, HIGH);
    digitalWrite(yellowled1, HIGH);
    digitalWrite(yellowled2, HIGH);
    digitalWrite(redled1, HIGH);
    digitalWrite(redled2, HIGH);
    Estado = 3;
    return Estado;
  }
  else if(distancia<21){
    digitalWrite(greenled1, HIGH);
    digitalWrite(greenled2, HIGH);
    digitalWrite(greenled3, HIGH);
    digitalWrite(greenled4, HIGH);
    digitalWrite(orangeled1, HIGH);
    digitalWrite(orangeled2, HIGH);
    digitalWrite(yellowled1, HIGH);
    digitalWrite(yellowled2, HIGH);
    digitalWrite(redled1, HIGH);
    digitalWrite(redled2, LOW);
    Estado = 3;
    return Estado;
  }
  else if(distancia<23){
    digitalWrite(greenled1, HIGH);
    digitalWrite(greenled2, HIGH);
    digitalWrite(greenled3, HIGH);
    digitalWrite(greenled4, HIGH);
    digitalWrite(orangeled1, HIGH);
    digitalWrite(orangeled2, HIGH);
    digitalWrite(yellowled1, HIGH);
    digitalWrite(yellowled2, HIGH);
    digitalWrite(redled1, LOW);
    digitalWrite(redled2, LOW);
    Estado = 3;
    return Estado;
  }
  else if(distancia<25){
    digitalWrite(greenled1, HIGH);
    digitalWrite(greenled2, HIGH);
    digitalWrite(greenled3, HIGH);
    digitalWrite(greenled4, HIGH);
    digitalWrite(orangeled1, HIGH);
    digitalWrite(orangeled2, HIGH);
    digitalWrite(yellowled1, HIGH);
    digitalWrite(yellowled2, LOW);
    digitalWrite(redled1, LOW);
    digitalWrite(redled2, LOW);
    Estado = 3;
    return Estado;
  }
  else if(distancia<28){
    digitalWrite(greenled1, HIGH);
    digitalWrite(greenled2, HIGH);
    digitalWrite(greenled3, HIGH);
    digitalWrite(greenled4, HIGH);
    digitalWrite(orangeled1, HIGH);
    digitalWrite(orangeled2, HIGH);
    digitalWrite(yellowled1, LOW);
    digitalWrite(yellowled2, LOW);
    digitalWrite(redled1, LOW);
    digitalWrite(redled2, LOW);
    Estado = 3;
    return Estado;
  }
  else if(distancia<30){
    digitalWrite(greenled1, HIGH);
    digitalWrite(greenled2, HIGH);
    digitalWrite(greenled3, HIGH);
    digitalWrite(greenled4, HIGH);
    digitalWrite(orangeled1, HIGH);
    digitalWrite(orangeled2, LOW);
    digitalWrite(yellowled1, LOW);
    digitalWrite(yellowled2, LOW);
    digitalWrite(redled1, LOW);
    digitalWrite(redled2, LOW);
    Estado = 3;
    return Estado;
  }
  else if(distancia<35){
    digitalWrite(greenled1, HIGH);
    digitalWrite(greenled2, HIGH);
    digitalWrite(greenled3, HIGH);
    digitalWrite(greenled4, HIGH);
    digitalWrite(orangeled1, LOW);
    digitalWrite(orangeled2, LOW);
    digitalWrite(yellowled1, LOW);
    digitalWrite(yellowled2, LOW);
    digitalWrite(redled1, LOW);
    digitalWrite(redled2, LOW);
    Estado = 3;
    return Estado;
  }
  else if(distancia<40){
    digitalWrite(greenled1, HIGH);
    digitalWrite(greenled2, HIGH);
    digitalWrite(greenled3, HIGH);
    digitalWrite(greenled4, LOW);
    digitalWrite(orangeled1, LOW);
    digitalWrite(orangeled2, LOW);
    digitalWrite(yellowled1, LOW);
    digitalWrite(yellowled2, LOW);
    digitalWrite(redled1, LOW);
    digitalWrite(redled2, LOW);
    Estado = 3;
    return Estado;
  }
    else if(distancia<45){
    digitalWrite(greenled1, HIGH);
    digitalWrite(greenled2, HIGH);
    digitalWrite(greenled3, LOW);
    digitalWrite(greenled4, LOW);
    digitalWrite(orangeled1, LOW);
    digitalWrite(orangeled2, LOW);
    digitalWrite(yellowled1, LOW);
    digitalWrite(yellowled2, LOW);
    digitalWrite(redled1, LOW);
    digitalWrite(redled2, LOW);
    Estado = 3;
    return Estado;
  }
  else if(distancia<50){
    digitalWrite(greenled1, HIGH);
    digitalWrite(greenled2, LOW);
    digitalWrite(greenled3, LOW);
    digitalWrite(greenled4, LOW);
    digitalWrite(orangeled1, LOW);
    digitalWrite(orangeled2, LOW);
    digitalWrite(yellowled1, LOW);
    digitalWrite(yellowled2, LOW);
    digitalWrite(redled1, LOW);
    digitalWrite(redled2, LOW);
    Estado = 3;
    return Estado;
  }
  else if (distancia>30){
    digitalWrite(greenled1, LOW);
    digitalWrite(greenled2, LOW);
    digitalWrite(greenled3, LOW);
    digitalWrite(greenled4, LOW);
    digitalWrite(orangeled1, LOW);
    digitalWrite(orangeled2, LOW);
    digitalWrite(yellowled1, LOW);
    digitalWrite(yellowled2, LOW);
    digitalWrite(redled1, LOW);
    digitalWrite(redled2, LOW);
    Estado = 3;
    return Estado;
  }
  }
