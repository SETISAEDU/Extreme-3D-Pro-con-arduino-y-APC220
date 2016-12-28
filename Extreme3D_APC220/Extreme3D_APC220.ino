/*
 * Codigo para le recepcion de los datos del Extreme 3D Pro por medio del APC220 
 * desarrollado por SETISAEDU
 */
#include <Servo.h> //Libreria para el uso de servomotores
//Uso del constructor para generar los objetos de control de los servos  
Servo servoX,servoY,servoS,servoT;
void setup() {
  // Inicializacion de los puertos seriales
  //Serial.begin(250000); //Solo para depuracion
  Serial1.begin(57600); //Puerto de recepcion de los dados

   //Configuracion de los pines de salida para cada servo
   servoX.attach(3);
   servoY.attach(5);
   servoS.attach(7);
   servoT.attach(9);

  //Declaracion de los pines de los LED como salidas, solo arduino Mega o Due por la cantidad y disposicion de pines
  for(int j=22;j<42;j++)
  {
    pinMode(j,OUTPUT);
  }
//  Serial.println("iniciado"); //Solo para depuracion
}

void loop() {
  //Espera de datos provinientes del modulo RF
  if(Serial1.available())
  {
   String data = Serial1.readStringUntil('\n');
   if(data.length()>14 &&  data.length()<29)
    {
      
      uint8_t x_ = data.indexOf("x");
      uint8_t y_ = data.indexOf("y");
      uint8_t h = data.indexOf("h");
      uint8_t t = data.indexOf("t");
      uint8_t s = data.indexOf("s");
      uint8_t a = data.indexOf("a");
      uint8_t b = data.indexOf("b");
      uint8_t f = data.indexOf("\n");
      
      String Sx = data.substring(x_+1,y_);
      String Sy = data.substring(y_+1,h);
      String Ssw = data.substring(h+1,t);
      String Stwist = data.substring(t+1,s);
      String Sslider = data.substring(s+1,a);
      String SbA = data.substring(a+1,b);
      String SbB = data.substring(b+1,f);

      int x       = Sx.toInt();
      int y       = Sy.toInt();
      int sw      = Ssw.toInt();
      int twist   = Stwist.toInt();
      int slider  = Sslider.toInt();
      int buttonA = SbA.toInt();
      int buttonB = SbB.toInt();

/*      Solo para el caso de depuracion de los datos
*/
//      Serial.print(x);
//      Serial.print(" ");
//      Serial.print(y);
//      Serial.print(" ");
//      Serial.print(sw);
//      Serial.print(" ");
//      Serial.print(twist);
//      Serial.print(" ");
//      Serial.print(slider);
//      Serial.print(" ");
//      Serial.print(buttonA);
//      Serial.print(" ");
//      Serial.println(buttonB);

      //Actualizacion de los valores de las salidas                                    
      short int mul[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80}; //Vector para generar la discriminacion
      //Impresion de los valores a los pines digitales
      for(int i=0;i<8;i++)
      {
        digitalWrite(22+i,buttonA&mul[i]);
        digitalWrite(34+i,sw&mul[i]);
      }
      for(int i=0;i<4;i++)
      {
        digitalWrite(30+i,buttonB&mul[i]);
      }
      
      //Actualizacion de las posiciones de los servos
      servoX.write(map(x,0,1023,15,180));
      servoY.write(map(y,0,1023,15,180));
      servoS.write(map(slider,0,255,15,180));
      servoT.write(map(twist,255,0,15,180)); //Se invierte para que sea igual a el giro de la palanca
    
    }
  }
  
}
