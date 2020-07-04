
////////////////////////////////////////////
//       variable de lectura de datos     //
////////////////////////////////////////////
const byte SPACE_DATA = 64; // los caracteres maximo a leer 
bool end_read_new_data = false; // si hay nuevo ddatos 
char serial_data_from_pc[SPACE_DATA]; // donnde se guarda los datos 



////////////////////////////////////////////
//      varaibale de interpretacion       //
////////////////////////////////////////////
const byte MOTOR_N = 7;  // CANTIDAD DE MOTOR
long step_[MOTOR_N];     // los pasos 
bool dir_[MOTOR_N];      // la direcion
long speed_[MOTOR_N];    // la velocidad
 
        // definiciones de interpretacion

#define AXIS_X 0
#define AXIS_Y 1
#define AXIS_Z 2
#define AXIS_A 3
#define AXIS_B 4
#define AXIS_C 5
#define AXIS_NOT_FIND 6

#define AXIS_COMMAND 9
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




/////////////////////////////////////////////////////////
//                                                     //
//                                                     //
//      FUNCION PRINCIPAL PARA LA LECTURA DE DATOS     //
//                                                     //
//                                                     //
/////////////////////////////////////////////////////////
void _main_read(){

  _read_from_pc();
  if(end_read_new_data == true){
    Serial.println(serial_data_from_pc);
    _interpretar();
    end_read_new_data = false;
    _remove_data();
  }
  
   
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

// borrar los datos de la variable de lectura
void _remove_data(){

  memset(serial_data_from_pc,0,sizeof(serial_data_from_pc));
}

  ////////////////////////////////////////////////
  //             separacion de los datos        //
  ////////////////////////////////////////////////

void _interpretar(){

  
  byte last_motor; // indice del motor a mover 
  last_motor = AXIS_NOT_FIND; // valor por defecto del motor 

  // recorre todo el texto guardado para ver el motor 
  for (byte i = 0; i < SPACE_DATA; i ++){

    // segun el comando ingresado tomara una accion o otra 
    switch (serial_data_from_pc[i]){
       // EJE X    
       case 'X':

          __set_step(i,AXIS_X);
          last_motor = AXIS_X;
          break;
       // EJE Y    
       case 'Y':

          __set_step(i,AXIS_Y);
          last_motor = AXIS_Y;
          break;
        // EJE Z    
       case 'Z':
          
          __set_step(i,AXIS_Z);
          last_motor = AXIS_Z;
          break;
       // EJE A
       case 'A':
          
          __set_step(i,AXIS_A);
          last_motor = AXIS_A;
          
          break;

       //EJE B
       case 'B':

          __set_step(i,AXIS_B);
          last_motor = AXIS_B;
          break;

       //EJE C
       case 'C':

          __set_step(i,AXIS_C);
          last_motor = AXIS_C;
          break;

       // VELOCIDAD 
       case 'F':

          __set_speed(i,last_motor);
          /*
          Serial.println("motor " + String(last_motor));
          Serial.println("pasos");
          Serial.println(step_[last_motor]);
          Serial.println("velocidad");
          Serial.println(speed_[last_motor]);
          Serial.println("direcion");
          Serial.println(dir_[last_motor]);
    */
          break;
       
       
       // heramientas 
        
       case 'L': // laser

          break;

       case 'S': // servo motor

          break;

       case 'P': // pwm 

          break;

       
    }
  }
  
}



// TRADUCE LA DIRECCION Y LA VELOCIDA 
void __set_step(int index, int motor){
    
  step_[motor] = ___translate_data(index);// interpreta los datos 


  // compara si es negativo o positivo para ver la direcion 
  if (step_[motor] > 0){

    
    dir_[motor] = true;
    
  }else {
    dir_[motor] = false;
  }
  // valor abusoluto
  step_[motor] = abs(step_[motor]);
}

// TRANDUCE LA VELOCIDAD 
void __set_speed(int index, int motor){

  speed_[motor] = ___translate_data(index);
  speed_[motor] = abs(speed_[motor]);
}

/////////////////////////////////////////////////////////
//                                                     //
//                                                     //
//      FUNCION PRINCIPAL PARA LA LECTURA DE DATOS     //
//                                                     //
//                                                     //
/////////////////////////////////////////////////////////



// traduce los datos y debuelve un long 
long ___translate_data(int index){
  
    char data[AXIS_COMMAND]; // guardar el sub tesxto 
    long result;  // varaible a retornar 
    // guarda los datos pertinente 
    
    for (int i = 0 ; i < AXIS_COMMAND ; i ++){
      data[i] = serial_data_from_pc[i+index+1];
    }

    result = atol(data);// tranforma esos caracteres a numero 
    return result;
}
