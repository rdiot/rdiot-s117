#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include <NRF905.h>
#include <SPI.h>
#define BUF_LEN          32
#define CONF_LEN         10

//NRF905 nrf905;

unsigned char rx_buf[BUF_LEN]= {0};
unsigned char read_config_buf[CONF_LEN];
unsigned char rx_address[4]= {0xcc,0xcc,0xcc,0xcc};
String str1="";

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x20 for a 16 chars and 2 line display

void putstring(unsigned char *str)
{
    
    while(*str){
        str1 += char(*str++);
        //Serial.write(*str++);   
        
    }
}

void setup()
{
    char i;
    pinMode(10,OUTPUT);
    nrf905=NRF905(10);
    
    /** pin/port configuration */
    nrf905.init(); 

  
    /***************************************************
        default configuration, need to specify frequency
        choose Z-Wave frequency band, support :
        US		908.42Mhz
        EUROPE		868.42MHz
        AFRICA		868.42MHz
        CHINA		868.42MHz
        HK		919.82MHz
        JAPAN		853.42MHz
        AUSTRALIA	921.42MHz
        NEW_ZEALAND	921.42MHz
        BRASIL		921.42MHz
        RUSSIA		896MHz
    */ 
	nrf905.write_config(US); 	
    
    /***********************************************************
	read register configuration, check register value written */
    nrf905.read_config(read_config_buf);
    
    /** serial communication configurate */
    Serial.begin(9600);
    
    /** test configuration */
    for(i=0; i<CONF_LEN; i++){
        Serial.print(read_config_buf[i],HEX);
        Serial.print(' ');
    }

  lcd.init();  // initialize the lcd 
  lcd.backlight();
  lcd.print("start LCD2004");
 
  delay(1000);
 
  lcd.clear();
    
}

void loop()
{

    lcd.setCursor(0,0);
    lcd.print("S117:nRF905 RCV");
  
    /** recieve data packet with default RX address */
    nrf905.RX(rx_buf);
    
    /** recieve data packet with specified RX address */
//    nrf905.RX(rx_buf, rx_address );
    
    // NOTE: TX_Address and RX_Address must be the same
    
    /** send recieved data to PC through serial port */
    
    

    putstring(rx_buf);

    lcd.setCursor(0,1);  
    lcd.print(str1);
    str1 = "";

  
    
    delay(1);
}

