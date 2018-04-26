#include <NewPing.h>
 
/*Aqui se configuran los pines donde debemos conectar el sensor*/
#define TRIGGER_PIN  13
#define ECHO_PIN     12
#define MAX_DISTANCE 400
 
/*Crear el objeto de la clase NewPing*/
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
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
int alarm = 11;

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
  pinMode(alarm,OUTPUT);
}
 
void loop() {
  int distancia1=sensor1();
  controlleds(distancia1);
  controlintensidad(distancia1);
  alarma_distancia(distancia1);
}

int sensor1(){
     // Esperar 1 segundo entre mediciones
  delay(300);
  // Obtener medicion de tiempo de viaje del sonido y guardar en variable uS
  int uS = sonar.ping_median();
  int distancia = (uS / US_ROUNDTRIP_CM);
  // Imprimir la distancia medida a la consola serial
  Serial.print("Distancia: ");
  // Calcular la distancia con base en una constante
  Serial.print(uS / US_ROUNDTRIP_CM);
  Serial.println("cm");
  return distancia;
}
void controlintensidad(int intensidad){
  analogWrite(luzprincipal1,intensidad);
  analogWrite(luzprincipal2,intensidad);
  }

void alarma_distancia(int distancia){
    if (distancia < 18){
    digitalWrite(alarm, HIGH);
    delay(200);
    digitalWrite(alarm, LOW);
    delay(100);
    }
    else{
    digitalWrite(alarm, LOW);
    }
  }


void controlleds(int distancia){
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
    delay (300);}
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
  }
}
