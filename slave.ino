#include <avr/io.h>  // библиотека ввода/вывода которая объяснит компилятору какие порты ввода/вывода есть у микроконтроллера
#include <stdio.h> //определения макросов, константы и объявления функций и типов
#include <stdlib.h> //анимающиеся выделением памяти, контролем процесса выполнения программы, преобразованием типов и другие
#include <util/delay.h>  // библиотека для задержек
#define F_CPU 1000000UL

void UART_settings (unsigned int ubrr) //unsigned int ubrr--> пример кода есть в даташит
{
	
	UCSR0A |= (1<<U2X0); // Удвоение скорости передачи данных
	
	UCSR0B = (1<<RXEN0) | (1<<TXEN0); // разрешаем работу приемника и передатчика
	
	UCSR0C = (0<<UMSEL01) | (0<<UMSEL00) |(1<<USBS0) | (0<<UCSZ02) | (1<<UCSZ01) | (1<<UCSZ00); // асинхронный режим, 2-а стоп-бита, 8 бит данных посылка
	
	//задаем скорость передачи данных табл. в даташит 20.11.5, код есть в дата шит 20.5
	UBRR0H = (unsigned char)(ubrr >> 8);//сдвигаем на 8 позиций в право
	
	UBRR0L = (unsigned char)(ubrr);
}
unsigned char USART_Receive( void )//table 20.7.1
{
	/* Wait for data to be received */
	while(! (UCSR0A & (1 << RXC0)) )
	;
	/* Get and return received data from buffer */
	return UDR0;
}

void PWM_settings_1 (void)
{
	TCCR1A |= (1<<COM1A1);
	TCCR1A &= ~(1<<COM1A0); // НЕинвертирующая  быстродействующая ШИМ- пилообразная форма импульсов опорного напряжения

	TCCR1A |= (1<<WGM10); // 8 бит ШИМ, быстро действ.
	TCCR1A &= ~(1<<WGM11); // 8 бит ШИМ, быстро действ.
	TCCR1B |= (1<<WGM12); // 8 бит ШИМ, быстро действ.
	TCCR1B &= ~(1<<WGM13); // 8 бит ШИМ, быстро действ.

	TCCR1B |= (1<<CS11); // Делим частоту МК на 8
	TCCR1B &= ~((1<<CS10)|(1<<CS12)); // Делим частоту МК на 8 = 125000
	// timer counter control register (0 pin B-настраиваемый, 8-битный) делим частоту счетчика на (8*1024)/1000000=0,008 сек . Частота = 1024\0,008
	// 1000000 / (8*1024)=122 частота работы шим
}

void PWM_settings_2 (void)
{
	TCCR1A |= (1<<COM1B1); // НЕинвертирующая  быстродействующая ШИМ- пилообразная форма импульсов опорного напряжения
	TCCR1A &= ~ (1<<COM1B0);
	
	TCCR1A |= (1<<WGM10); // 8 бит ШИМ, быстро действ.
	TCCR1A &= ~(1<<WGM11); // 8 бит ШИМ, быстро действ.
	TCCR1B |= (1<<WGM12); // 8бит ШИМ, быстро действ.
	TCCR1B &= ~(1<<WGM13); // 8 бит ШИМ, быстро действ.

	TCCR1B |= (1<<CS11); // Делим частоту МК на 8
	TCCR1B &= ~((1<<CS10)|(1<<CS12)); // Делим частоту МК на 8 = 125000
	// timer counter control register (0 pin B-настраиваемый, 8-битный) делим частоту счетчика на (8*1024)/1000000=0,008 сек . Частота = 1024\0,008
	// 1000000 / (8*1024)=122 частота работы шим
}

void PWM_settings_3 (void)
{
	TCCR0A |= (1<<COM0A1);
	TCCR0A &= ~ (1<<COM0A0); // НЕинвертирующая ШИМ
	
	TCCR0A |= (1<<WGM00); // 8 бит ШИМ, быстро действ.
	TCCR0A |= (1<<WGM01); // 8 бит ШИМ, быстро действ.
	TCCR0B &= ~ (1<<WGM02); // 8 бит ШИМ, быстро действ.
	
	TCCR0B &= ~((1<<CS00) | (1<<CS02)); // Делим частоту МК на 8
	TCCR0B |= (1<<CS01); // Делим частоту МК на 8
	
}

void PWM_settings_4 (void)
{
	TCCR0A |= (1<<COM0B1);
	TCCR0A &= ~ (1<<COM0B0); // НЕинвертирующая ШИМ
	
	TCCR0A |= (1<<WGM00); // 8 бит ШИМ, быстро действ.
	TCCR0A |= (1<<WGM01); // 8 бит ШИМ, быстро действ.
	TCCR0B &= ~ (1<<WGM02); // 8 бит ШИМ, быстро действ.
	
	TCCR0B &= ~((1<<CS00) | (1<<CS02)); // Делим частоту МК на 8
	TCCR0B |= (1<<CS01); // Делим частоту МК на 8
	
}

int main(void)
{
	UART_settings(12); // Задаем скорость передачи данных 9600 бод
	// при Fмк = 1000000 Гц, U2X = 1
	
// 	DDRB= 0b00000110;//подключаем светодиод
// 	PORTB=0b00000000;
	
	PWM_settings_1 ();
	PWM_settings_2 ();
	PWM_settings_3 ();
	PWM_settings_4 ();
	
	while (1)

	{
		while (! (UCSR0A & (1 << RXC0)) );

		if (UDR0 == 0b10000000)
		{
			DDRD = 0b01000000; // чем ниже ШИМ,тем больше напряжения идет на моторы

			OCR0A = 254;
			DDRB = 0b00000010; // чем ниже ШИМ,тем больше напряжения идет на моторы

			OCR1A = 250;
		}
		else if (UDR0 == 0b11000000)
		{
			DDRD = 0b01000000;

			OCR0A = 150;
			DDRB = 0b00000010;

			OCR1A = 150;
		
		}
		else if (UDR0 == 0b11100000)
		{
			DDRD = 0b01000000;
			
			OCR0A= 70;
			DDRB = 0b00000010;
			
			OCR1A= 70;
			
		}
		else if (UDR0 == 0b11110000)
		{
			DDRD = 0b01000000;
			
			OCR0A= 50;
			DDRB = 0b00000010;
			
			OCR1A = 50;
		}
		else if (UDR0 == 0b11111000)
		{
			DDRD = 0b00000000;
			// среднее значение ШИМ, показатель ШИМ и напряжение в рановесии
			OCR0A = 0;
			OCR0B = 0;
		}
		else if (UDR0 == 0b11111100)
		{
			DDRD = 0b00100000;
			
			OCR0B = 50;
			DDRB = 0b00000100;
			
			OCR1B = 50;
		}
		else if (UDR0 == 0b10100000)
		{
				DDRD = 0b00100000;
				
				
				OCR0B = 70;
				DDRB = 0b00000100;
				
				
				OCR1B = 70;
		}
		else if (UDR0 == 0b10101000)
		{
			DDRD = 0b00100000;
			
			
			OCR0B= 150;
			DDRB = 0b00000100;
			
			
			OCR1B= 150;
		}
		else if (UDR0 == 0b10101010)
		{
			DDRD = 0b00100000;
			
			
			OCR0B= 190;
			DDRB = 0b00000100;
			
			
			OCR1B= 190;
		}
		else if (UDR0 == 0b11101010)
		{
			DDRD = 0b00100000;
			
			OCR0B= 254;
			DDRB = 0b00000100;
			
			OCR1B= 254;
			}
			
			//another ADC
			
			else if (UDR0 == 0b00000001)
			{
				DDRB = 0b00000010; // чем ниже ШИМ,тем больше напряжения идет на моторы

				OCR1A = 250;
				DDRD = 0b00100000;
				
				OCR0B= 254;
			}
			else if (UDR0 == 0b00000011)
			{
				DDRB = 0b00000010;

				OCR1A = 150;
				DDRD = 0b00100000;
				
				
				OCR0B= 150;
				
			}
			else if (UDR0 == 0b00000111)
			{
				DDRB = 0b00000010;
				
				OCR1A= 70;
				DDRD = 0b00100000;
				
				
				OCR0B = 70;
				
			}
			else if (UDR0 == 0b00001111)
			{
				DDRB = 0b00000010;
				
				OCR1A = 50;
				DDRD = 0b00100000;
				
				OCR0B = 50;
			}
			else if (UDR0 == 0b00011111)
			{
				DDRB = 0b00000000;
				// среднее значение ШИМ, показатель ШИМ и напряжение в рановесии
				OCR1A = 0;
				OCR1B = 0;
			}
			else if (UDR0 == 0b00111111)
			{
				DDRB = 0b00000100;
				
				OCR1B = 50;
				DDRD = 0b01000000;
				
				OCR0A= 50;
			}
			else if (UDR0 == 0b01111111)
			{
				DDRB = 0b00000100;
				
				
				OCR1B = 70;
				DDRD = 0b01000000;
				
				OCR0A= 70;
			}
			else if (UDR0 == 0b01111101)
			{
				DDRB = 0b00000100;
				
				
				OCR1B= 150;
				DDRD = 0b01000000;

				OCR0A = 150;
			}
			else if (UDR0 == 0b01110101)
			{
				DDRB = 0b00000100;
				
				
				OCR1B= 190;
				DDRD = 0b01000000;

				OCR0A = 190;
			}
			else if (UDR0 == 0b01010101)
			{
				DDRB = 0b00000100;
				
				OCR1B= 254;
				DDRD = 0b01000000;

				OCR0A = 254;
			}
			
	}
}