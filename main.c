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


// �adowanie biblitek 
#include "LCD/lcd44780.h"
#include "dht11/dht.h"


// notka dla MS
#define EEMEM __attribute__((section(".eeprom")))


int main(void)
{
	// inicjalizacja LCD
	DDRC |= (1<<PC5);	// ustawiamy kierunek linii pod�wietlenia LCD jako WYJ�CIE
	
	PORTC |= (1<<PC5);	// za��czamy pod�wietlenie LCD - stan wysoki

	
	
	

	_delay_ms(1000);		//inicjalizacja LCD
	lcd_init();
	
	int8_t temperatura = 0;		//zmienne dla dht
	int8_t wilgotnosc = 0;
	
	
	
	

	while(1){
		// wywo�anie funkcji odczytu 
		if(dht_gettemperaturehumidity(&temperatura, &wilgotnosc) != -1) {
			
			lcd_cls();

			lcd_home();
			lcd_int(temperatura);
			
			lcd_locate(1,0);
			lcd_int(wilgotnosc);

		}else{
			
			// jesli z czujnikiem b�dzie co� nie tak, zwr�ci error
			lcd_cls();
			lcd_home();
			lcd_str("ERROR CZUJNIKA");
		}
		
		_delay_ms(500);
		
		
	}
}

