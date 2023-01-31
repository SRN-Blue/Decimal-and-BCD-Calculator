#include <mega16.h>

// Alphanumeric LCD functions
#include <alcd.h>
#include <delay.h>
#include <string.h>
#include <io.h>

#define keypin PINB 


char read_key = '\0', read_val = '\0' ;       // variable read_key to store current value og ABCD of MM74c992,
                                              // to store numbers against values of ABXCD

// Declare your global variables here
int input_numbers[20];
int counter = 0;
int counter2 = 0;
char req_operator;
int result_length;
int result_is_Fnumber = 1;
int result_holder = 1568;

int toggledetecter;
int modeprintconsent;

// counters Var
int summation_first = 0;
int z=0;
int start = 0;
int resetercounter;

// Calculation vars
int fnumber = 0;
int snumber = 0;
int tensplus = 1;
int localforcharholder;
int end;
int resultintarray[20];
//int resultresume[20];
int localwhilecounter = 0;

int result = 0;

// Reversed var
int temp;


void BcdCalculator(char num){

    switch (num) {
    case '0':
        lcd_puts("0000");
        lcd_puts(" ");
        break;
    case '1':
        lcd_puts("0001");
        lcd_puts(" ");
        break;
    case '2':
        lcd_puts("0010");
        lcd_puts(" ");
        break;
    case '3':
        lcd_puts("0011");
        lcd_puts(" ");
        break;
    case '4':
        lcd_puts("0100");
        lcd_puts(" ");
        break;
    case '5':
        lcd_puts("0101");
        lcd_puts(" ");
        break;
    case '6':
        lcd_puts("0110");
        lcd_puts(" ");
        break;
    case '7':
        lcd_puts("0111");
        lcd_puts(" ");
        break;
    case '8':
        lcd_puts("1000");
        lcd_puts(" ");
        break;
    case '9':
        lcd_puts("1001");
        lcd_puts(" ");
        break;
    default:
        lcd_puts("Only Numbers are are accepted!");
        break;
}
}





void reseter(){
    // till summation
    counter = 0;
    counter2 = 0;
    req_operator = '0';
    result_is_Fnumber = 1;

    // counters Var
    summation_first = 0;
    z=0;
    start = 0;

    // summation vars
    fnumber = 0;
    snumber = 0;
    tensplus = 1;
    localwhilecounter = 0;

    resetercounter = 0;
    for(resetercounter;resetercounter<20;resetercounter++){
        resultintarray[resetercounter] = 0;   
    }  
    localwhilecounter = 0;
    for(resetercounter;resetercounter<20;resetercounter++){
        input_numbers[resetercounter] = 0;   
    }

    result = 0; 
    // till summation   

    lcd_clear ();
    if(PIND.6 == 1){
        lcd_puts("Calculate Mode");
        delay_ms(500);  
        lcd_clear (); 
      } 
      else{
        lcd_puts("Converter Mode");
        delay_ms(500);  
        lcd_clear (); 
      }
//    lcd_puts("Calculate Mode");
//    delay_ms(500);
//    lcd_clear ();   
}


void inttochar(int num){
   
    if(num==0){
        lcd_putchar('0');      
    }
    else if(num==1){
        lcd_putchar('1');     
    }
    else if(num==2){ 
        lcd_putchar('2'); 
    }
    else if(num==3){
        lcd_putchar('3'); 
    }
    else if(num==4){ 
        lcd_putchar('4'); 
    }
    else if(num==5){
        lcd_putchar('5'); 
    }
    else if(num==6){
        lcd_putchar('6'); 
    }
    else if(num==7){
        lcd_putchar('7'); 
    }
    else if(num==8){ 
        lcd_putchar('8'); 
    }
    else if(num==9){ 
        lcd_putchar('9'); 
    }
    
   // return charnum;    
}


int chartoint(char num){
    int intnum;    
   
    if(num=='0'){
        intnum = 0; 
    }
    else if(num=='1'){
        intnum = 1;    
    }
    else if(num=='2'){
        intnum = 2;    
    }
    else if(num=='3'){
        intnum = 3;    
    }
    else if(num=='4'){
        intnum = 4;    
    }
    else if(num=='5'){
        intnum = 5;    
    }
    else if(num=='6'){
        intnum = 6;    
    }
    else if(num=='7'){
        intnum = 7;    
    }
    else if(num=='8'){
        intnum = 8;    
    }
    else if(num=='9'){
        intnum = 9;    
    }
    
    return intnum;
}      


void resume_reseter1(){
    int intsplit; 
    lcd_clear ();

    // till summation
    counter = 0;
    counter2 = 0;
    req_operator = '0';
    result_is_Fnumber = 1;

    // counters Var
    summation_first = 0;
    z=0;
    start = 0;

    // summation vars
    fnumber = 0;
    snumber = 0;
    tensplus = 1;
    localwhilecounter = 0;

    resetercounter = 0;
    for(resetercounter;resetercounter<20;resetercounter++){
        resultintarray[resetercounter] = 0;   
    }  
    localwhilecounter = 0;
    for(resetercounter;resetercounter<20;resetercounter++){
        input_numbers[resetercounter] = 0;   
    } 
     
    input_numbers[resetercounter] = 3;
    input_numbers[resetercounter] = 1;
    counter = 2;
        
}


void resume_reseter2(){
    int intsplit; 
    lcd_clear ();

    // till summation
    counter = 0;
    counter2 = 0;
    req_operator = '0';
    result_is_Fnumber = 1;

    // counters Var
    summation_first = 0;
    z=0;
    start = 0;

    // summation vars
    fnumber = 0;
    snumber = 0;
    tensplus = 1;
    localwhilecounter = 0;

    resetercounter = 0;
    for(resetercounter;resetercounter<20;resetercounter++){
        resultintarray[resetercounter] = 0;   
    }  
    localwhilecounter = 0;
    for(resetercounter;resetercounter<20;resetercounter++){
        input_numbers[resetercounter] = 0;   
    }

    result = 0; 
    // till summation 
    PORTA.1 = 0;
    while (result_holder > 0) {
        intsplit = result_holder % 10;
        result_holder = result_holder / 10;    
        delay_ms(500);
        read_val = 0x0f & keypin ;    // only take lower 4 bits i.e. value of ABCD and set all other bits to zero
        switch (intsplit){  
           case 9 :
                PORTA.2 =  1;
                PORTA.3 =  0;
                PORTA.4 =  0;
                PORTA.5 =  0;
                PORTA.0 = 1; // triggers external intrupt (int0)
                delay_ms(100);
                PORTA.0 = 0; // triggers external intrupt (int0)
                break;
           case 8 :
                PORTA.2 =  0;
                PORTA.3 =  1;
                PORTA.4 =  0;
                PORTA.5 =  0; 
                PORTA.0 = 1; // triggers external intrupt (int0)
                delay_ms(100);
                PORTA.0 = 0; // triggers external intrupt (int0)
                break;
           case 7 : 
                PORTA.2 =  1;
                PORTA.3 =  1;
                PORTA.4 =  0;
                PORTA.5 =  0; 
                PORTA.0 = 1; // triggers external intrupt (int0)
                delay_ms(100);
                PORTA.0 = 0; // triggers external intrupt (int0)
                break;
           case 6 :
                PORTA.2 =  1;
                PORTA.3 =  0;
                PORTA.4 =  1;
                PORTA.5 =  0; 
                PORTA.0 = 1; // triggers external intrupt (int0)
                delay_ms(100);
                PORTA.0 = 0; // triggers external intrupt (int0)
                break;
           case 5 :
                PORTA.2 =  0;
                PORTA.3 =  1;
                PORTA.4 =  1;
                PORTA.5 =  0;
                PORTA.0 = 1; // triggers external intrupt (int0)
                delay_ms(100);
                PORTA.0 = 0; // triggers external intrupt (int0)
                break;
           case 4 : 
                PORTA.2 =  1;
                PORTA.3 =  1;
                PORTA.4 =  1;
                PORTA.5 =  0; 
                PORTA.0 = 1; // triggers external intrupt (int0)
                delay_ms(100);
                PORTA.0 = 0; // triggers external intrupt (int0)
                break;
           case 3 : 
                PORTA.2 =  1;
                PORTA.3 =  0;
                PORTA.4 =  0;
                PORTA.5 =  1; 
                PORTA.0 = 1; // triggers external intrupt (int0)
                delay_ms(100);
                PORTA.0 = 0; // triggers external intrupt (int0)
                break;
           case 2 : 
                PORTA.2 =  0;
                PORTA.3 =  1;
                PORTA.4 =  0;
                PORTA.5 =  1; 
                PORTA.0 = 1; // triggers external intrupt (int0)
                delay_ms(100);
                PORTA.0 = 0; // triggers external intrupt (int0)
                break;
           case 1 :
                PORTA.2 =  1;
                PORTA.3 =  1;
                PORTA.4 =  0;
                PORTA.5 =  1; 
                PORTA.0 = 1; // triggers external intrupt (int0)
                delay_ms(100);
                PORTA.0 = 0; // triggers external intrupt (int0)
                break;
           case 0 : 
                PORTA.2 =  0;
                PORTA.3 =  1;
                PORTA.4 =  1;
                PORTA.5 =  1;
                PORTA.0 = 1; // triggers external intrupt (int0) 
                delay_ms(100);
                PORTA.0 = 0; // triggers external intrupt (int0)
                break;                                                                                                                                                                                              
        } 
//        PORTA.1 = 0; // triggers external intrupt (int0)
//        delay_ms(30);
//        PORTA.1 = 1; // triggers external intrupt (int0)
    } 
    
    PORTA.1 = 1; // triggers external intrupt (int0)
    
}


void Calculate(){
    int intsplit; 
    // getting first number 
    for(summation_first;summation_first<(counter2-1);summation_first++){
        tensplus = tensplus * 10;   
    }
    summation_first = 0;
    for(summation_first;summation_first<(counter2);summation_first++){
        fnumber = fnumber + (input_numbers[summation_first] * tensplus);
        tensplus = tensplus / 10;      
    }
    
    // return global variables to initial for calculating second number
    summation_first = 0;
    tensplus = 1;
    
    // getting second number
    for(summation_first;summation_first<(counter-counter2)-1;summation_first++){
        tensplus = tensplus * 10;   
    }
    summation_first = counter2;
    for(summation_first;summation_first<counter;summation_first++){ //+1 removed
        snumber = snumber + (input_numbers[summation_first] * tensplus);
        tensplus = tensplus / 10;      
    }
    
    // Main calculate function
    if(req_operator == '+'){
        result =  fnumber + snumber;  // result in intiger form    
    } 
    else if(req_operator == '*'){
        result =  fnumber * snumber;  // result in intiger form    
    }
    else if(req_operator == '/'){
        result =  fnumber / snumber;  // result in intiger form    
    }
    else if(req_operator == '-'){
        result =  fnumber - snumber;  // result in intiger form    
    }
    else if(req_operator == '0'){
        lcd_putchar ('E');
        result =  0;  // Getting Error   
    }
    
    result_holder = result;
    summation_first = 0;
    lcd_clear ();
    if(result == 0){                          
        lcd_putchar ('0');       
    }
       
   // int resultintarray[20];
    localwhilecounter = 0;
    
    while(result > 0){
        intsplit = result % 10;
        result = result / 10;  
        resultintarray[localwhilecounter] = intsplit;
        localwhilecounter++;
    }                       
    
    result_length =  (localwhilecounter-1);
    // Reverser
    start = 0;
    end = (localwhilecounter-1);
    while (start < end)
    { 
      temp = resultintarray[start];  
      resultintarray[start] = resultintarray[end];
      resultintarray[end] = temp;
      start++;
      end--;
    }
    // Reverser
    
    z=0;
    for(z;z<localwhilecounter;z++){
      localforcharholder = resultintarray[z];
      inttochar(localforcharholder);
    } 
    
    
}


interrupt [EXT_INT0] void ext_int0_isr(void)
{
// Place your code here
    read_val = 0x0f & keypin ;    // only take lower 4 bits i.e. value of ABCD and set all other bits to zero
    switch (read_val){   // switch statement to check all  possible combination of ABCD and save the value of digit ti read_val
       case 0x00 :                    // there is 16 casae(for all 16 combination)
            read_key = '/' ;
            break;
       case 0x01 :
            read_key = '9' ;
            break;
       case 0x02 :
            read_key = '8' ;
            break;
       case 0x03 :
            read_key = '7' ;
            break;
       case 0x04 :
            read_key = '*' ;
            break;
       case 0x05 :
            read_key = '6' ;
            break;
       case 0x06 :
            read_key = '5' ;
            break;
       case 0x07 :
            read_key = '4' ;
            break;
       case 0x08 :
            read_key = '-' ;
            break;
       case 0x09 :
            read_key = '3' ;
            break;
       case 0x0a :
            read_key = '2' ;
            break;
       case 0x0b :
            read_key = '1' ;
            break;
       case 0x0c :
            read_key = '+' ;
            break;
       case 0x0d :
            read_key = '=' ;
            break;
       case 0x0e :
            read_key = '0' ;
            break;
       case 0x0f :
            read_key = 'R' ;
            break;
                                                                                                                                                                                                 
    }  
    
//     lcd_putchar (read_key); // put this digit on LCD  
    if(PIND.6 == 1){   // Calculate Mode                     
        lcd_putchar (read_key); // put this digit on LCD
        if(read_key == '+' || read_key == '-' || read_key == '*' || read_key == '/'){
            // if read operator
            counter2 = counter;
            req_operator = read_key; // get the operator for function
            
        }              
        else if(read_key == '='){
            Calculate();
            delay_ms(1000); 
            resume_reseter1();
        }
        else if(read_key == 'R'){
            // if reseted  
            reseter();
        } 
        else{
            // Numbers Here
            input_numbers[counter] = chartoint(read_key); // get and store numbers
            counter++;
        }  
    }
    else{      // BCD Converter
        if(read_key == 'R'){
            // if reseted  
            reseter();
        }
        else{
            // if get number
            BcdCalculator(read_key);
        }
    }
    
}





void main(void)
{
// Declare your local variables here
DDRB = 0x00;
PORTB = 0xff;
DDRC = 0xff;
PORTC = 0x00;

// Input/Output Ports initialization
// Port A initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRA=(1<<DDA7) | (1<<DDA6) | (1<<DDA5) | (1<<DDA4) | (1<<DDA3) | (1<<DDA2) | (1<<DDA1) | (1<<DDA0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (1<<PORTA1) | (1<<PORTA0);

// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRC=(0<<DDC7) | (0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (0<<DDC0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTD=(0<<PORTD7) | (1<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=0xFF
// OC0 output: Disconnected
TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (0<<CS02) | (0<<CS01) | (0<<CS00);
TCNT0=0x00;
OCR0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=0xFFFF
// OC1A output: Disconnected
// OC1B output: Disconnected
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (0<<CS11) | (0<<CS10);
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer2 Stopped
// Mode: Normal top=0xFF
// OC2 output: Disconnected
ASSR=0<<AS2;
TCCR2=(0<<PWM2) | (0<<COM21) | (0<<COM20) | (0<<CTC2) | (0<<CS22) | (0<<CS21) | (0<<CS20);
TCNT2=0x00;
OCR2=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);

// External Interrupt(s) initialization
// INT0: On
// INT0 Mode: Rising Edge
// INT1: Off
// INT2: Off
GICR|=(0<<INT1) | (1<<INT0) | (0<<INT2);
MCUCR=(0<<ISC11) | (0<<ISC10) | (1<<ISC01) | (1<<ISC00);
MCUCSR=(0<<ISC2);
GIFR=(0<<INTF1) | (1<<INTF0) | (0<<INTF2);

// USART initialization
// USART disabled
UCSRB=(0<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (0<<RXEN) | (0<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);

// Analog Comparator initialization
// Analog Comparator: Off
// The Analog Comparator's positive input is
// connected to the AIN0 pin
// The Analog Comparator's negative input is
// connected to the AIN1 pin
ACSR=(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);
SFIOR=(0<<ACME);

// ADC initialization
// ADC disabled
ADCSRA=(0<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (0<<ADPS1) | (0<<ADPS0);

// SPI initialization
// SPI disabled
SPCR=(0<<SPIE) | (0<<SPE) | (0<<DORD) | (0<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);

// TWI initialization
// TWI disabled
TWCR=(0<<TWEA) | (0<<TWSTA) | (0<<TWSTO) | (0<<TWEN) | (0<<TWIE);

// Alphanumeric LCD initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTC Bit 0
// RD - PORTC Bit 1
// EN - PORTC Bit 2
// D4 - PORTC Bit 4
// D5 - PORTC Bit 5
// D6 - PORTC Bit 6
// D7 - PORTC Bit 7
// Characters/line: 8
lcd_init(8);

// Global enable interrupts
#asm("sei")

lcd_puts("Hello   User!");
delay_ms(500);
lcd_clear ();

if(PIND.6 == 1){
        lcd_puts("Calculate Mode");
        delay_ms(500);  
        lcd_clear (); 
      } 
      else{
        lcd_puts("Converter Mode");
        delay_ms(500);  
        lcd_clear (); 
      }


toggledetecter = PIND.6;
modeprintconsent = 1;
}

