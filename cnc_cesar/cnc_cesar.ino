
////////////////////////////////////////////
//       variable de lectura de datos     //
////////////////////////////////////////////
const byte SPACE_DATA = 50;
bool end_read_data = false;

char serial_data_from_pc[SPACE_DATA];


void setup() {
  // put your setup code here, to run once:
  
  
  ////////////////////////////////////////////////
  //             lectura de datos               //
  ////////////////////////////////////////////////
  
  Serial.begin(115200);
  delay(100);
  Serial.println("super CNC by Cesar");
}

void loop() {
  // put your main code here, to run repeatedly:
  
}


  ////////////////////////////////////////////////
  //             lectura de datos               //
  ////////////////////////////////////////////////
void _read_from_pc() {

  byte count_data = 0;

  // lee todo los datos que estan el bufet
  if(Serial.available() > 0){

    
  }
}
