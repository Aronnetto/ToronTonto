#include <Servo.h>

const int sensorPin2 = 7; // Pin donde está conectado OUT del sensor
const int ledPin = 13;   // LED incorporado del Arduino
int sensorState;

int sensorPin = 12; // Pin donde está conectado OUT del sensor pelota
int valorSensorPelota = 0;
int analog[] = {A0, A1, A2, A3, A4, A5, A6, A7};
int D[8];
 
float error;
float errorant=0;
float correccion=0;
float integral=0;
float diferencial=0;

bool tengoPelota;

Servo servoizq;
Servo servoder;
Servo garra;
Servo brazo;


long dis;

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin2, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  servoder.attach(4);
  servoizq.attach(5);
  garra.attach(8);
  brazo.attach(9);
  pinMode(sensorPin, INPUT);
  servoder.write(0);
  servoizq.write(0);
  delay(3000);
  garra.write(80); // giro hacia afuera y queda pronta para agarrar
  delay(250);     // 
  garra.write(90); //al inicuar el programa hay que dejar la garra cerrada
  delay(1000);
  brazo.write(180);
  tengoPelota=false;
}

void loop(){ 
  //Distancia();
  sensorState = digitalRead(sensorPin2);
  //Serial.println(dis);
  valorSensorPelota = digitalRead(sensorPin);
  if ((sensorState ==  0)&&(tengoPelota == false)){
    delay(1000);
    garra.write(100);
    digitalWrite(ledPin, HIGH);
    tengoPelota == true;
    delay(1000);
    valorSensorPelota = digitalRead(sensorPin);
     if(valorSensorPelota == 0){
      delay(1000);
      Levantar();
      digitalWrite(ledPin, LOW);
     }
     
    }
  
  // chequeo de distancia al costado
   //if((dis <= 26) && (dis > 20)){
        // prisma 
        //tirarPrisma();
        
     //if (tengoPelota) {
      // tirarPrisma(); 
     //} 
    //} 
   
   /*if (dis <= 17){
      while (dis <= 17)  {
            // portico
        //adelante(10); 
        Distancia();
      }
  // al salir del portico tirar la pelota
     if (tengoPelota) {
       tirarPortico(); 
     }*/ 
    
   //}
    
  // Seguidor de linas
/*
 for (int i=0;i<=7;i++) {
    if (analogRead(analog[i])>950){
      D[i]=1;
    }
    else {
      D[i]=0;
    }
    //Serial.print(analog[i]);
    //Serial.print("= ");
    //Serial.print(analogRead(analog[i]));
    //Serial.print("  ");
    
  }
  //Serial.println("");
   error=100*D[0] + 50*D[1] + 25*D[2] + 1*D[3] + -1*D[4] + -25*D[5] + -50 *D[6]+ -100 *D[7];
   //Serial.println(error);
   diferencial=error-errorant;
   integral = error/10+integral;
   errorant=error;
   correccion= (error/1.9) + 0*diferencial + 0*(integral);
   seguir(40, correccion);
   //Serial.println("LINEAAAA");
*/
}




void Levantar (){ //hay que cambiarle para que solo levante etc.
   brazo.write(0); //sube hasta posición deseada, pot 60 durante 0,8 seg
   delay(600);
   garra.write(90); //esperamos a que el brazo suba 
   delay(600);
   garra.write(80); //giro hacia afuera y queda pronta para agarrar
   delay(250);
   garra.write(90);
   brazo.write(180); // baja para agarrar de nuevo, pot 120 durante 0,6 seg
   delay(400);
}

void seguir(int v, float correccion) {
  servoder.write(parallax(-v - correccion));
  servoizq.write(parallax(v -correccion));
}

void izquierda(int v) {
  servoder.write(parallax(-v ));
  servoizq.write(parallax(-v));

}

void derecha(int v) {
  servoder.write(parallax(v));
  servoizq.write(parallax(v));
}

void atras(int v) {
  servoder.write(parallax(v));
  servoizq.write(parallax(-v));
}

void parar() {
  servoder.write(parallax(0));
  servoizq.write(parallax(0));
 
}

void adelante(int v) {
  servoder.write(parallax(-v));
  servoizq.write(parallax(v));
}

int parallax(float velocidad){  //velocidad es un parámetro que tenemos que setear entre -100 y 100. 
    return int(1500+(velocidad/100)*250);
     }


/*void Distancia() {
  long t;
  digitalWrite(T1, HIGH);
  delayMicroseconds(10);
  digitalWrite(T1,LOW);
  t = pulseIn(E1, HIGH);
  dis = t/59;
}*/
