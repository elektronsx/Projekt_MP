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


// notka dla MS
#define EEMEM __attribute__((section(".eeprom")))


int main(void)
{
	// inicjalizacja LCD
	DDRC |= (1<<PC5);	// ustawiamy kierunek linii podœwietlenia LCD jako WYJŒCIE
	
	PORTC |= (1<<PC5);	// za³¹czamy podœwietlenie LCD - stan wysoki

	
	
	

	_delay_ms(1000);		//inicjalizacja LCD
	lcd_init();
	
	int8_t temperatura = 0;		//zmienne dla dht
	int8_t wilgotnosc = 0;
	
	
	
	

	while(1){
		// wywo³anie funkcji odczytu 
		if(dht_gettemperaturehumidity(&temperatura, &wilgotnosc) != -1) {
			
			lcd_cls();

			lcd_home();
			lcd_int(temperatura);
			
			lcd_locate(1,0);
			lcd_int(wilgotnosc);

		}else{
			
			// jesli z czujnikiem bêdzie coœ nie tak, zwróci error
			lcd_cls();
			lcd_home();
			lcd_str("ERROR CZUJNIKA");
		}
		
		_delay_ms(500);
		
		
	}
}

