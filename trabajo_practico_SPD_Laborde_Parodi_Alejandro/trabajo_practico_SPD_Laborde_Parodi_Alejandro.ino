#include <LiquidCrystal.h>
#define btnRIGHT 0
#define btnUP 1
#define btnDOWN 2
#define btnLEFT 3
#define btnSELECT 4
#define btnNONE 5

LiquidCrystal lcd(8,9,4,5,6,7);

int bit1=-1;
int bit2=-1;
int bit3=-1;
int bit4=-1;
int LecturaBoton;

bool estado=0;

int PosCursorX=2;




/**********************************************************
***********************************************************
***********************************************************
**************************************************************/

void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
    pinMode(11,OUTPUT);
    pinMode(A3,OUTPUT);
    pinMode(A4,OUTPUT);
    pinMode(A5,OUTPUT);
    pinMode(13,OUTPUT);
   pinMode(12,OUTPUT);
   pinMode(10,OUTPUT);
  
    lcd.setCursor(8,0);
    lcd.print("SELECT");
    lcd.setCursor(7,1);
    lcd.print("TO START"); 
    apagaLEDS();
  

}

void loop()
{
  
   delay(100);
    LecturaBoton=read_LCD_buttons();
    if(LecturaBoton==4 && bit1==-1 && bit2==-1 && bit3==-1 && bit4==-1) estado=1;
  PosCursorX = set_Cursor(PosCursorX,LecturaBoton,estado);
  print_Cursor(PosCursorX);
  
    if(LecturaBoton==1 || LecturaBoton==2 && estado==1)
    {
      if(PosCursorX==0) bit1=!bit1;
      if(PosCursorX==1) bit2=!bit2;
      if(PosCursorX==2) bit3=!bit3;
      if(PosCursorX==3) bit4=!bit4; 
    }
  MuestraNumero_LCD(bit1,bit2,bit3,bit4);
  
  if(LecturaBoton==4 && bit1!=-1 && bit2!=-1 && bit3!=-1 && bit4!=-1){
    apagaLEDS();
    MuestraNumero_LED(bit1,bit2,bit3,bit4);
    delay(5000);
    
    if((bit1 + bit2 + bit4)%2 !=0){Serial.print("1");}else{Serial.print("0");}                                                      
    if((bit1 + bit3 + bit4)%2 !=0){Serial.print("1");}else{Serial.print("0");}
    Serial.print(bit1);
     if((bit2 + bit3 + bit4)%2 !=0){Serial.print("1");}else{Serial.print("0");}
    Serial.print(bit2);
    Serial.print(bit3);                                                         
    Serial.print(bit4);  
    
   /* if((bit1 + bit2 + bit4)%2 !=0){digitalWrite(13,0);}
    if((bit1 + bit3 + bit4)%2 !=0){digitalWrite(12,0);}
    if((bit2 + bit3 + bit4)%2 !=0){digitalWrite(10,0);}*/
  }
  
  
}


/****************************************************************
***********************************************************
***********************************************************
***********************************************************/
void apagaLEDS(){
  digitalWrite(13,1);
    digitalWrite(12,1);
    digitalWrite(11,1);
    digitalWrite(10,1);
    digitalWrite(A3,1);
    digitalWrite(A4,1);
    digitalWrite(A5,1);
}





void MuestraNumero_LCD(int b1, int b2, int b3, int b4)
{
  lcd.setCursor(0,0);
  if(b1 != -1){ lcd.print(b1);}else{lcd.print("*");}
  lcd.setCursor(1,0);
  if(b2 != -1){ lcd.print(b2);}else{lcd.print("*");}
  lcd.setCursor(2,0);
  if(b3 != -1){ lcd.print(b3);}else{lcd.print("*");}
  lcd.setCursor(3,0);
  if(b4 != -1){ lcd.print(b4);}else{lcd.print("*");}
}

void MuestraNumero_LED(int b1, int b2, int b3, int b4)
{
  if(b1==1){digitalWrite(11, 0);}else{digitalWrite(11,1);}
  if(b2==1){digitalWrite(A3, 0);}else{digitalWrite(A3,1);}
  if(b3==1){digitalWrite(A4, 0);}else{digitalWrite(A4,1);}
  if(b4==1){digitalWrite(A5, 0);}else{digitalWrite(A5,1);}
}



int set_Cursor(int PosCursorX, int LecturaBoton, int estado){
    
    if(LecturaBoton==0 || LecturaBoton==3 && estado==1)
    {
      if(LecturaBoton==3 && PosCursorX>-1)
      {
        PosCursorX--;
      }else
      {
        if(PosCursorX<3) PosCursorX++;
      }
    }
  
    return PosCursorX;
  
}

void print_Cursor(int PosCursorX){
  
    for(int i=0;i<5;i++)
    {
     lcd.setCursor(i,1);
     lcd.print(" ");
    }
   if(PosCursorX>-1 && PosCursorX<5){
     lcd.setCursor(PosCursorX,1);
     lcd.print("-");
  }
}




int read_LCD_buttons(void)
{
  int lcd_key = btnNONE;
  int adc_key_in = 0;
  delay(100);
  adc_key_in = analogRead(0);
  if (adc_key_in > 1000)
    lcd_key = btnNONE; 
  else if (adc_key_in < 50) 
    lcd_key = btnRIGHT;
  else if (adc_key_in < 195) 
    lcd_key = btnUP;
  else if (adc_key_in < 380) 
    lcd_key = btnDOWN;
  else if (adc_key_in < 555)  
    lcd_key = btnLEFT;
  else if (adc_key_in < 790) 
    lcd_key = btnSELECT;

  return lcd_key; 
}


