#include <main.h>
#define bat_tat PIN_B4
#define thuan_nghich PIN_B5
#define HallA PIN_B0
#define HallB PIN_B1
#define HallC PIN_B2
//#define ana PIN_A0


unsigned int16 tocdo; 
int1 state=0; 
int1 dir=1;

void quaythuan()
{
   if (input(HallA)==1 && input(HallB)==0 && input(HallC)==1) {output_d(0b00010001);} 
   else if (input(HallA)==1 && input(HallB)==0 && input(HallC)==0) {output_d(0b00100001);} 
   else if (input(HallA)==1 && input(HallB)==1 && input(HallC)==0) {output_d(0b00100010);} 
   else if (input(HallA)==0 && input(HallB)==1 && input(HallC)==0) {output_d(0b00001010);} 
   else if (input(HallA)==0 && input(HallB)==1 && input(HallC)==1) {output_d(0b00001100);} 
   else if (input(HallA)==0 && input(HallB)==0 && input(HallC)==1) {output_d(0b00010100);} 
}

void quaynghich()
{
   if (input(HallA)==1 && input(HallB)==0 && input(HallC)==1) {output_d(0b00001010);}
   else if (input(HallA)==1 && input(HallB)==0 && input(HallC)==0) {output_d(0b00001100);}
   else if (input(HallA)==1 && input(HallB)==1 && input(HallC)==0) {output_d(0b00010100);}
   else if (input(HallA)==0 && input(HallB)==1 && input(HallC)==0) {output_d(0b00010001);}
   else if (input(HallA)==0 && input(HallB)==1 && input(HallC)==1) {output_d(0b00100001);}
   else if (input(HallA)==0 && input(HallB)==0 && input(HallC)==1) {output_d(0b00100010);}
}
void main()
{
   set_tris_b(0xff); 
   set_tris_d(0x00); 
   set_tris_c(0); 
   set_tris_a(0x01); 
   setup_adc_ports(sAN0);
   setup_adc(ADC_CLOCK_INTERNAL);
   set_adc_channel(0);
   setup_timer_2(T2_DIV_BY_16, 255, 1);
   setup_ccp1(CCP_PWM);
   while(TRUE)
   {

      tocdo = read_adc();
      delay_us(50); 
      set_pwm1_duty(tocdo);
      if(input(bat_tat)==0)
      {
         delay_ms(20);
         if(input(bat_tat)==0)
         {
            while(input(bat_tat)==0); 
            state = !state;
         }
      }
      if(input(thuan_nghich)==0)
      {
         delay_ms(20);
         if(input(thuan_nghich)==0)
         {
            while(input(thuan_nghich)==0);
            dir = !dir;
         }
      }
      if(state==0) 
      {
         output_d(0x00); 
      }
      else 
      {
         if(dir==0) quaythuan();
         else quaynghich();
      }     
  }
}

