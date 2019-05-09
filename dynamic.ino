int in_ADC ;
int Vol , out_DAC1; 
void setup()
{
  
  //ADC Configuration
  ADC->ADC_MR |= 0x80;   // Free Running Mode // Mode Register
  ADC->ADC_CR=2;         // Starts ADC conver. // CR = Control Register 
  ADC->ADC_CHER=0x780;  // Enable ADC channels 0,8  //  0100 1000 0000 (10 7 0)// CHER = Channel Enable Register 
 
  //DAC Configuration
  analogWrite(DAC1,0);  // Enables DAC1  
}
 
void loop()

{
  //Read the ADCs
  while((ADC->ADC_ISR & 0x780)!=0x780);// wait for ADC 0,8 conversion complete. // ISR = Interrupt Status Register 
  in_ADC=ADC->ADC_CDR[7];               // read data from ADC0 // CDR = Channel Data Register
  Vol=ADC->ADC_CDR[10];                 // read data from ADC8        

  //Volume
  
  out_DAC1=map(in_ADC,0,4095,0,Vol);
  
  dacc_set_channel_selection(DACC_INTERFACE, 1);          //select DAC channel 1
  dacc_write_conversion_data(DACC_INTERFACE, out_DAC1);   //write on DAC

 
}
