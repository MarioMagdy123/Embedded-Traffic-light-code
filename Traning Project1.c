char segment[] = {0x00,0x10,0x20,0x30,0x40,0x50,0x60,0x70,0x80,0x90,0x01,0x11,0x21,0x31,0x41,0x51,0x61,0x71,0x81,0x91,0x02,0x12,0x22,0x32};
int i ,counter=0;
#define Traffic_red1    porte.B0
#define Traffic_yellow1 porte.B1
#define Traffic_green1  porte.B2
#define Traffic_red2    porta.B0
#define Traffic_yellow2 porta.B1
#define Traffic_green2  porta.B2
void interrupt(){
 if (intf_bit==1 )
 {
    intf_bit=0;
    counter++;

    if(counter%2==1)
    {
       portb=0b11111110;
       porte=0;
       porta=0;
       Traffic_red1=1;
       Traffic_yellow2=1;
       delay_ms(3000);
       Traffic_yellow2=0;
       Traffic_green2=1;
    }
    else
    {
       portb=0b11111110;
       porte=0;
       porta=0;
       Traffic_red2=1;
       Traffic_yellow1=1;
       delay_ms(3000);
       Traffic_yellow1=0;
       Traffic_green1=1;
    }
  }
}

void main() {
        adcon1=7;          //to change port A & E to analog
        trisa=0;           //define port A as output
        trisb=0B00000001;  //define port B as output and pin 0 to input
        trisc=0;           //define port C as output
        trise=0;           //define port E as output
        gie_bit=1;
        inte_bit=1;
        intedg_bit=0;
        porta=0;           //remove garbage value
        portc=0;           //remove garbage value
        porte=0;           //remove garbage value
        portb=0;           //remove garbage value
        trisa.b4=1;        //define pin 4 at port A to input

        while(1)
        {    if( porta.B4==0 )      //check manual or automatic
              {
               trisb.B0=1;             // change port b.b0 to input
               portb=0b11111110;       //turn of seven segments displays
              }
              else 
              {
               trisb.B0=0;         // change port b.b0 to output
              }
              
              
             while(porta.B4==0);       //to hold if changed to manual
             
              portb=1;
              porte=0;
              porta=0;
              Traffic_red1=1;
              Traffic_green2=1;
              trisb.b0=0;
       for (i=23 ; i>=0;i--)          //to count from 23 to 0 on the seven segment display
            {
                if(porta.B4==0)     // to stop if manual mode started
                {
                  porte=0;
                  porta=0;
                  portc=0;
                  break;
                }
                
                portc = segment[i];      //send numbers to seven segment display
                if (i>3) 
                {
                 delay_ms(1000);
                }
                else 
                {
                  Traffic_green2=0;
                  Traffic_yellow2=1;           // change from green to yellow at the last 3 sec
                  delay_ms(1000);
                }
            }
            Traffic_yellow2=0;
            Traffic_red1=0;
            Traffic_red2=1;
            Traffic_green1=1;
       for(i=15;i>=0;i--)                 //to count from 15 to 0 on the seven segment display
             {
               if(porta.B4==0)            // to stop if manual mode started
                {
                  porte=0;
                  porta=0;
                  portc=0;
                  break;
                }
               portc=segment[i];         //send numbers to seven segment display
               if (i>3)
                {
                 delay_ms(1000);
                }
              else 
                {
                 Traffic_green1 =0;
                 Traffic_yellow1=1;       // change from green to yellow at the last 3 sec
                 delay_ms(1000);
                }
              }
               Traffic_yellow1=0;
               Traffic_red2=0;
             }
       
       }