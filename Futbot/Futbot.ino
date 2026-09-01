
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>


//Contraseña del robot, tanto el mando como el robot deben usar la misma
#define password "admin123"
//Nombre del Robot. Este es el nombre que aparecera en el Bluetooth
#define name "LionelMessi"

int watchDogOn=0;
int passLog=0;
char Letra = 0;
unsigned int Letra2=0;

const int ENA = 6;
const int ENB = 7;

const int IN1 = 1;
const int IN2 = 3;
const int IN3 = 4;
const int IN4 = 5;

long int stopTime=-1;
long int currentTime=0;
long int noAction=0;

const int DEAD_TIME=10000;



int Velocidad = 171;

#define SERVICE_UUID        "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"


void parar();

class RXCallbacks : public BLECharacteristicCallbacks {

  void onWrite(BLECharacteristic *pCharacteristic) {

    String dato = pCharacteristic->getValue();

    if (dato.length() > 0) {

      // Contraseña de seguridad para usar el Futbot, tanto el mando como el robot deben usar la misma
      if(dato==password){
        passLog=1;

      }

      Letra = dato[0];
      Serial.print("BLE: ");
      Serial.print(Letra);
            
      
       
      if(Letra=='Q'&&dato.length()>1){
        Letra2 =dato[1];
        Serial.print("::");
        Serial.print(Letra2);
        
      }
      


      Serial.println("");
    }

    noAction=millis()+DEAD_TIME;
    
     if(!watchDogOn){
        watchDogOn=1;
      
        BLEDevice::getAdvertising()->stop();
     }
  }
};

class MyServerCallbacks : public BLEServerCallbacks {

  void onDisconnect(BLEServer* pServer) {
    parar();

    Serial.println("Desconectado");

    passLog=0;

    BLEDevice::startAdvertising();
  }

void onConnect(BLEServer* pServer) {
    
    passLog=0;
    noAction=millis()+DEAD_TIME;
    watchDogOn=1;
    Serial.println("Conectado");

    
  }
};

void adelante() {


  analogWrite(ENA, Velocidad);
  analogWrite(ENB, Velocidad);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}


void adelanteIzq(){



 analogWrite(ENA, Velocidad*65/100);
  analogWrite(ENB, Velocidad);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);



}

void adelanteDer(){


 analogWrite(ENA, Velocidad);
  analogWrite(ENB, Velocidad*65/100);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);



}

void atras() {


  analogWrite(ENA, Velocidad);
  analogWrite(ENB, Velocidad);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}


void atrasIzq() {



  analogWrite(ENA, Velocidad*65/100);
  analogWrite(ENB, Velocidad);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}


void atrasDer() {


  analogWrite(ENA, Velocidad);
  analogWrite(ENB, Velocidad*65/100);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}





void izquierda() {

  analogWrite(ENA, Velocidad*60/100);
  analogWrite(ENB, Velocidad*60/100);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void derecha() {

  analogWrite(ENA, Velocidad*60/100);
  analogWrite(ENB, Velocidad*60/100);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void girarIzquierda() {




  analogWrite(ENA, Velocidad);
  analogWrite(ENB, Velocidad);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}


void girarDerecha() {



  analogWrite(ENA, Velocidad);
  analogWrite(ENB, Velocidad);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void cambiarVelocidad(int vel){


  Velocidad=vel;
}

void maxVelocidad(){
  
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
}

void atrapar(){

int i=1,speed=255;

  stopTime=millis()+30;
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  i=0;
  while(Letra=='X'){
    
    currentTime=millis();
     
    if(currentTime>stopTime){
      stopTime=currentTime+30;
      speed=255-i*i;
        i++;
      if(speed>-1) {
          analogWrite(ENA, speed);
          analogWrite(ENB, speed);
      }
          else {speed=0;
          parar();
          Letra='#';
      }
      
    }
    delay(10);
    
   
}
Letra='#';


}

void patear(){



  stopTime=millis()+350;

    analogWrite(ENA, 255);
    analogWrite(ENB, 255);

    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

while(Letra=='T'){
      currentTime=millis();

    if(currentTime>stopTime){
      Letra='#';
      parar();
    }
    delay(10);
   
}

}

void patearIzq(){



  stopTime=millis()+350;
    analogWrite(ENA, 200);
  analogWrite(ENB, 255);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  while(Letra=='U'){
      currentTime=millis();

    if(currentTime>stopTime){
      Letra='#';
      parar();
    }
    delay(10);
   
  }



}

void patearDer(){



  stopTime=millis()+350;
  analogWrite(ENA, 255);
  analogWrite(ENB, 200);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  while(Letra=='O'){
      currentTime=millis();

    if(currentTime>stopTime){
      Letra='#';
      parar();
    }
    delay(10);
   
  }


}






void parar() {



  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  
}



void remolino(){

int i=0;
   
  stopTime=millis()+150;

  girarIzquierda();
  while(Letra=='G'&&currentTime<stopTime){
    currentTime=millis();
    delay(10);
  }
  parar();


  for(i=0;i<5&&Letra=='G';i++){
      stopTime=millis()+300;

      girarDerecha();
      while(Letra=='G'&&currentTime<stopTime){
          currentTime=millis();
          delay(10);
        }
        parar();

      stopTime=millis()+300;

      girarIzquierda();
      while(Letra=='G'&&currentTime<stopTime){
          currentTime=millis();
          delay(10);
        }
      parar();
  }

 stopTime=millis()+150;

  girarDerecha();
  while(Letra=='G'&&currentTime<stopTime){
    currentTime=millis();
    delay(10);
  }
  parar();






}



void correrIzq(){

 stopTime=millis()+150;

  girarIzquierda();
  while(Letra=='D'&&currentTime<stopTime){
    currentTime=millis();
    delay(10);
  }
  parar();

stopTime=millis()+300;

  adelante();
  while(Letra=='D'&&currentTime<stopTime){
    currentTime=millis();
    delay(10);
  }
  parar();


  stopTime=millis()+300;

  girarDerecha();
  while(Letra=='D'&&currentTime<stopTime){
    currentTime=millis();
    delay(10);
  }
  parar();




  stopTime=millis()+300;

  atras();
  while(Letra=='D'&&currentTime<stopTime){
    currentTime=millis();
    delay(10);
  }
  parar();




  stopTime=millis()+150;

    girarIzquierda();
    while(Letra=='D'&&currentTime<stopTime){
      currentTime=millis();
      delay(10);
    }
    parar();




}

void correrDer(){

 stopTime=millis()+150;

  girarDerecha();
  while(Letra=='K'&&currentTime<stopTime){
    currentTime=millis();
    delay(10);
  }
  parar();

stopTime=millis()+300;

  adelante();
  while(Letra=='K'&&currentTime<stopTime){
    currentTime=millis();
    delay(10);
  }
  parar();


  stopTime=millis()+300;

  girarIzquierda();
  while(Letra=='K'&&currentTime<stopTime){
    currentTime=millis();
    delay(10);
  }
  parar();




  stopTime=millis()+300;

  atras();
  while(Letra=='K'&&currentTime<stopTime){
    currentTime=millis();
    delay(10);
  }
  parar();




  stopTime=millis()+150;

    girarDerecha();
    while(Letra=='K'&&currentTime<stopTime){
      currentTime=millis();
      delay(10);
    }
    parar();




}




void setup() {

  Serial.begin(115200);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  parar();

  BLEDevice::init(name);

  BLEServer *pServer = BLEDevice::createServer();

  BLEService *pService =
      pServer->createService(SERVICE_UUID);

  BLECharacteristic *pCharacteristic =
      pService->createCharacteristic(
          CHARACTERISTIC_UUID,
          BLECharacteristic::PROPERTY_WRITE
      );

  pCharacteristic->setCallbacks(new RXCallbacks());
  pServer->setCallbacks(new MyServerCallbacks());

  pService->start();

  BLEAdvertising *pAdvertising =
      BLEDevice::getAdvertising();

  pAdvertising->start();

  Serial.println("Robot listo");

  currentTime=millis();

  noAction=currentTime+DEAD_TIME;
}

void loop() {



  currentTime=millis();

  if(currentTime>noAction&&watchDogOn) {
    parar();
    watchDogOn=0;

   

            BLEDevice::startAdvertising();
        

  }

      if (Serial.available()) {

        Letra = Serial.read();

        Serial.print("USB: ");
        Serial.println(Letra);
      }


  if(passLog){
      switch (Letra) {

        case 'F':
          Serial.println("Adelante");
          adelante();
          Letra='#';
          break;

        case 'B':
        Serial.println("Atras");
          atras();
          Letra='#';
          break;

        case 'L':
        Serial.println("Izquierda");
          izquierda();
          Letra='#';
          break;

        case 'R':
        Serial.println("Derecha");
          derecha();
          Letra='#';
          break;

        case 'P':
        case 'p':
        Serial.println("Parada");
          parar();
          Letra='#';
          break;


        case 'T':
        Serial.println("Patear");
          patear();
          Letra='#';
          break;


          case 'U':
        Serial.println("Patear Izq");
          patearIzq();
          Letra='#';
          break;

          case 'O':
        Serial.println("Patear Der");
          patearDer();
          Letra='#';
          break;

          case 'Q':
        Serial.print("Velocidad");
        Serial.println(Letra2);
        cambiarVelocidad(Letra2);
          Letra='#';
          break;

          case 'A':
        Serial.println("Turbo!!");
          maxVelocidad();
          Letra='#';
          break;


          case 'q':
        Serial.println("Adelante-Izquierda");
          adelanteIzq();
          Letra='#';
          break;


          case 'e':
        Serial.println("Adelante-Derecha");
          adelanteDer();
          Letra='#';
          break;



          case 'z':
        Serial.println("Atras-Izquierda");
          atrasIzq();
          Letra='#';
          break;


          case 'c':
        Serial.println("Atras-Derecha");
          atrasDer();
          Letra='#';
          break;


            case 'X':
        Serial.println("Atrapar Pelota");
          atrapar();
          Letra='#';
          break;

          case 'S':
        Serial.println("Girar Izquierda");
          girarIzquierda();
          Letra='#';
          break;

          case 'C':
        Serial.println("Girar Derecha");
          girarDerecha();
          Letra='#';
          break;


          case 'G':
        Serial.println("Remolino");
          remolino();
          Letra='#';
          break;

          case 'D':
        Serial.println("Correr Izq");
          correrIzq();
          Letra='#';
          break;

          case 'K':
        Serial.println("Correr Der");
          correrDer();
          Letra='#';
          break;


      }
    }
  delay(10);
}
