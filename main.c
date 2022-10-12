/*
 * LCD_1.c
 *
 * Created: 15.05.2022 10:59:05
 * Author : oldti
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>


// ³adowanie biblitek 
#include "LCD/lcd44780.h"
#include "dht11/dht.h"



#define EEMEM __attribute__((section(".eeprom")))

const char PROGMEM tab1[] = {"FLASH"};
char EEMEM tab2[] = {"EEPROM"};

uint8_t znak_L[] = {16,16,18,20,24,16,31,0};		// wzór znaku litery £ w pamiêci RAM
uint8_t znak_o[] EEMEM = {4,32,14,17,17,17,14,0};	// wzór znaku litery ó w pamiêci EEPROM
const uint8_t znak_buzka[] PROGMEM = {14,17,27,17,17,21,17,14};	// wzór znaku buŸki w pamiêci FLASH
const uint8_t znak_termo[] PROGMEM = {4,10,10,10,17,31,31,14};	// wzór znaku termometru w pamiêci FLASH


//const char PROGMEM tab1[] = {"DZIALA"};

int main(void)
{
	// inicjalizacja LCD
	DDRC |= (1<<PC5);	// ustawiamy kierunek linii podœwietlenia LCD jako WYJŒCIE
	
	PORTC |= (1<<PC5);	// za³¹czamy podœwietlenie LCD - stan wysoki
	_delay_ms(1000);

	PORTC &= ~(1<<PC5);	// za³¹czamy podœwietlenie LCD - stan wysoki

	_delay_ms(1000);
	PORTC |= (1<<PC5);	// za³¹czamy podœwietlenie LCD - stan wysoki

	
	
	

	_delay_ms(1000);
	lcd_init();
	
	int8_t temperatura = 0;
	int8_t wilgotnosc = 0;
	
	
	
	

	while(1){
		
		if(dht_gettemperaturehumidity(&temperatura, &wilgotnosc) != -1) {
			
			lcd_cls();

			lcd_home();
			lcd_int(temperatura);
			
			lcd_locate(1,0);
			lcd_int(wilgotnosc);

		}
		
		_delay_ms(1500);
		
		
	}
}

