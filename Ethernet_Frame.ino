unsigned char CRC(char message[], unsigned char length) 
{ 
  const unsigned char CRC7_POLY = 0x91;   unsigned char i, j, crc = 0; 
 
  for (i = 0; i < length; i++) 
  { 
    crc ^= message[i];     for (j = 0; j < 8; j++) 
    {       
      if (crc & 1) 
        crc ^= CRC7_POLY; 
      crc >>= 1; 
    }   }   return crc; 
}
 
void setup() { 
   
Serial.begin(9600); // put your setup code here, to run once: 
 
}

 
void loop() {     
  
int SourceMACaddress = 0x02;        // 00-00-00-00-00-02
int DestinationMACaddress=0x01;     // 00-00-00-00-00-01
int counter=0
int sender=0,reciever=0;
int type;

if (Serial.available()) { 
  // Add Preamble
  // First 7 Bytes =>> 0b10101010 = 0xAA
  // Eighth Byte =>> 0b10101011 = 0xAB
  Serial.println("======================================================");
  Serial.println("Frame Received !");
  Serial.println("Preamble:");
  for(int i=0;i<7;i++){             
    while(!Serial.available()){}
    int data_rcvd = Serial.read();             
    Serial.print(data_rcvd, HEX);
    Serial.print(' ');
    if(data_rcvd == 0xAA){ 
      counter++; } 
  }
  
  while(!Serial.available()){}          
  int data_rcvd = Serial.read();          
  Serial.println(data_rcvd, HEX); 
  Serial.println(' ');
  if(data_rcvd==0xAB){ 
    counter++; }
       
  if(counter==8){ 
                
                
                while(!Serial.available()){}      
                // Add Destination Address 
                reciever=Serial.read();             
                while(!Serial.available()){}         
                sender=Serial.read();
                Serial.print("SRC MAC: 00-00-00-00-00-0");
                Serial.println(sender);
                Serial.print("DEST MAC: 00-00-00-00-00-0"); 
                Serial.println(reciever);
                Serial.println(' ');
                
                while(!Serial.available()){}  
                // Print type bits
                Serial.println("TYPE:");
                type=Serial.read();
                Serial.print(type, HEX); // Type byte
                Serial.print(" : ");
                Serial.println(type, HEX); // Type byte
                Serial.println(' ');
 
                if(reciever == SourceMACaddress){ 
                  
                  char data[20];                 
                  for(int j=0;j<20;j++){                   
                    while(!Serial.available()){}                   
                     data[j]=Serial.read(); 
                  }
                 
                  while(!Serial.available()){}                 
                  int m=Serial.read();
                  Serial.println("CRC:");
                  int z=CRC(data, 20);
                  Serial.println(z);
                  Serial.println(' ');
           
                  if(m==z){
                    Serial.println("No error was found!"); 
                  }                              
                  else{                     
                    Serial.println("There is an error in message!"); 
                  }
                    
                  Serial.print("Message: "); 
                  Serial.println(data); 
                  Serial.println(); 
                }
                else{ 
                    Serial.println("Wrong Address"); 
                }           
           }
   else{           
     Serial.println("Error!"); 
       }        
             
     }
 }


