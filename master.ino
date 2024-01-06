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
   
    //задаем скорость передачи данных  табл. в даташит 20.11.5, код есть в дата шит 20.5
    UBRR0H = (unsigned char)(ubrr >> 8);//сдвигаем на 8 позиций в право
   
    UBRR0L = (unsigned char)(ubrr);
}

void USART_Transmit( unsigned char data ) // пример кода есть в даташит 20.6.1
{

     while (!(UCSR0A & (1<<UDRE0)))
     ;
    /* Передаем данные в буфер данных */
    UDR0 = data;
}

void ADC_Init()			/* ADC Initialization function */
{
	ADMUX |= (1<<REFS0); // Опорное напряжение - внешние 5 В
	ADMUX &= ~(1<<REFS1);
	
	ADMUX &= ~(1<<ADLAR); // Правостороннее выравнивание
	
	ADMUX &= ~((1<<MUX3) | (1<<MUX2) | (1<<MUX1));// Задействуем 1-й вывод АЦП (РС1)
	ADMUX |= (1<<MUX0);
	
	ADCSRA |= (1<<ADEN); // Разрешаем работу АЦП
	//ADCSRA |= (1<<ADSC);	/* Start ADC conversion */
	ADCSRA |= (1<<ADATE); // Режим непрырывного измерения
	
	ADCSRA &= ~(1<<ADPS2); //делим частоту Мк на 8 - Устанавливаем частоту преобразования АЦП 125 000 Гц такие цифры нужны чтобы более точно отслеживать изменения (рекомендуется от 50 до 200 КГц)
	ADCSRA |= (1<<ADPS1) | (1<<ADPS0);
}

int ADC_Read(char channel)	/* ADC Read function */
{
	ADMUX = 0x40 | (channel & 0x03); //считывание показателей с разных пинов 1 и 0
	ADCSRA |= (1<<ADSC); // Запуск преобразования АЦП
	
	while (!(ADCSRA & (1<<ADIF))); // проверяем наличие 1 в реестре. Если 0, то начинаем считывание ацп.
	ADCSRA |= (1<<ADIF); // устанавливаем бит в 1, останавливаем работу АЦП. В ноль сбросится сам через несколько тактов.
	_delay_ms(1);
	return ADC;
}

int main(void)
{
    UART_settings(12); // Задаем скорость передачи данных 9600 бод
    // при Fмк = 1000000 Гц, U2X = 1
   // PORTC =0b00000001;//подключаем кнопку
   
    ADC_Init();		/* Initialize ADC */
            
    //Вход АЦП
 DDRC &= ~(1<<0);
 DDRC &= ~(1<<1);
  
    while (1)
    {
		
if(ADC_Read(0)<115)
		{
			{
				while (! (UCSR0A & (1 << UDRE0)) );
				{
					UDR0 = 0b10000000;//once transmitter is ready sent eight bit data
				}
			}
		}
		else if((ADC_Read(0)>=0) && (ADC_Read(0)<115))
		{
			{
				while (! (UCSR0A & (1 << UDRE0)) );
				{
					UDR0 = 0b11000000;//once transmitter is ready sent eight bit data
				}
			}
		}		
		else if ((ADC_Read(0)>=115) && (ADC_Read(0)<215))
		{
			{
				while (! (UCSR0A & (1 << UDRE0)) );
				{
					UDR0 = 0b11100000;//once transmitter is ready sent eight bit data
				}
			}
		}
		else if ((ADC_Read(0)>=215) && (ADC_Read(0)<315))
		{
			{
				while (! (UCSR0A & (1 << UDRE0)) );
				{
					UDR0 = 0b11110000;//once transmitter is ready sent eight bit data
				}
			}
		}
				else if ((ADC_Read(0)>=415) && (ADC_Read(0)<=575))
		{
		{
				while (! (UCSR0A & (1 << UDRE0)) );
				{
					UDR0 = 0b11111000;//once transmitter is ready sent eight bit data
				}
			}
		}
		else if((ADC_Read(0)>=585) && (ADC_Read(0)<615))
		{
			{
				while (! (UCSR0A & (1 << UDRE0)) );
				{
					UDR0 = 0b11111100;//once transmitter is ready sent eight bit data
				}
			}
		}
		
		else if ((ADC_Read(0)>=615) && (ADC_Read(0)<715))
		{
		 {
				 while (! (UCSR0A & (1 << UDRE0)) );
				 {
					 UDR0 = 0b10100000;//once transmitter is ready sent eight bit data
				 }
				
			 }
		}
		else if ((ADC_Read(0)>=715) && (ADC_Read(0)<815))
		{
			{
				while (! (UCSR0A & (1 << UDRE0)) );
				{
					UDR0 = 0b10101000;//once transmitter is ready sent eight bit data
				}
			}
		}
		
		else if ((ADC_Read(0)>=915) && (ADC_Read(0)<975))
		{
		{
				while (! (UCSR0A & (1 << UDRE0)) );
				{
					UDR0 = 0b10101010;//once transmitter is ready sent eight bit data
				}
			}
		}
		else if(ADC_Read(0)>=975)
		{
			{
				while (! (UCSR0A & (1 << UDRE0)) );
				{
					UDR0 = 0b11101010;//once transmitter is ready sent eight bit data
				}
			
			}
		}
      //another ADC
	  if(ADC_Read(1)<115)
	  {
		  {
			  while (! (UCSR0A & (1 << UDRE0)) );
			  {
				  UDR0 = 0b00000001;//once transmitter is ready sent eight bit data
			  }
		  }
	  }
	  else if((ADC_Read(1)>=0) && (ADC_Read(1)<115))
	  {
		  {
			  while (! (UCSR0A & (1 << UDRE0)) );
			  {
				  UDR0 = 0b00000011;//once transmitter is ready sent eight bit data
			  }
		  }
	  }
	  else if ((ADC_Read(1)>=115) && (ADC_Read(1)<215))
	  {
		  {
			  while (! (UCSR0A & (1 << UDRE0)) );
			  {
				  UDR0 = 0b00000111;//once transmitter is ready sent eight bit data
			  }
		  }
	  }
	  else if ((ADC_Read(1)>=215) && (ADC_Read(1)<315))
	  {
		  {
			  while (! (UCSR0A & (1 << UDRE0)) );
			  {
				  UDR0 = 0b00001111;//once transmitter is ready sent eight bit data
			  }
		  }
	  }
	  else if ((ADC_Read(1)>=415) && (ADC_Read(1)<=575))
	  {
		  {
			  while (! (UCSR0A & (1 << UDRE0)) );
			  {
				  UDR0 = 0b00011111;//once transmitter is ready sent eight bit data
			  }
		  }
	  }
	  else if((ADC_Read(1)>=585) && (ADC_Read(1)<615))
	  {
		  {
			  while (! (UCSR0A & (1 << UDRE0)) );
			  {
				  UDR0 = 0b00111111;//once transmitter is ready sent eight bit data
			  }
		  }
	  }
	  
	  else if ((ADC_Read(1)>=615) && (ADC_Read(1)<715))
	  {
		  {
			  while (! (UCSR0A & (1 << UDRE0)) );
			  {
				  UDR0 = 0b01111111;//once transmitter is ready sent eight bit data
			  }
			  
		  }
	  }
	  else if ((ADC_Read(1)>=715) && (ADC_Read(1)<815))
	  {
		  {
			  while (! (UCSR0A & (1 << UDRE0)) );
			  {
				  UDR0 = 0b01111101;//once transmitter is ready sent eight bit data
			  }
		  }
	  }
	  
	  else if ((ADC_Read(1)>=915) && (ADC_Read(1)<975))
	  {
		  {
			  while (! (UCSR0A & (1 << UDRE0)) );
			  {
				  UDR0 = 0b01110101;//once transmitter is ready sent eight bit data
			  }
		  }
	  }
	  else if(ADC_Read(1)>=975)
	  {
		  {
			  while (! (UCSR0A & (1 << UDRE0)) );
			  {
				  UDR0= 0b01010101;//once transmitter is ready sent eight bit data
			  }
			  
		  }
	  }
	  
	  }
	      
    }        

