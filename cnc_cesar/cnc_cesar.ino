
////////////////////////////////////////////
//       variable de lectura de datos     //
////////////////////////////////////////////
const byte SPACE_DATA = 64;
bool end_read_new_data = false;

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
  _main_read();
  delay(100);
}


  ////////////////////////////////////////////////
  //             lectura de datos               //
  ////////////////////////////////////////////////
void _read_from_pc() {

  byte count_data = 0; // contador 
  // lugar donde se guardan los datos 
  
  
  // lee todo los datos que estan el bufet
  if(Serial.available() > 0){
    end_read_new_data =true;  // ve si hay nuevos datos 
  }

  // lee y guarda los datos 
  while(Serial.available() > 0 ){

    // guarda los datos
    serial_data_from_pc[count_data] = Serial.read();

    //aumentar el contador
    count_data = count_data + 1;
  }
  
}


void remove_data(){

  memset(serial_data_from_pc,0,sizeof(serial_data_from_pc));
}

void _main_read(){

  _read_from_pc();
  if(end_read_new_data == true){
    Serial.println(serial_data_from_pc);
    end_read_new_data = false;
    remove_data();
  }
  
   
}
