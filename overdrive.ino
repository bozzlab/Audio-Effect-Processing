int in_ADC0, in_ADC1;  //variables for 2 ADCs valueds (ADC0, ADC1) //
int Vol,Drive,out_DAC0, out_DAC1; //variables for 3 pots (ADC8, ADC9, ADC10)// 
const int LED = 3; // 
const int FOOTSWITCH = 7; // 
const int TOGGLE = 2; // 
int high_threshold, low_threshold ,s1_threshold,s2_threshold,s3_threshold,s4_threshold,s5_threshold,s6_threshold,drive_controlA,drive_controlB;//

 
void setup()
{
  
  //ADC Configuration
  ADC->ADC_MR |= 0xC0;   // DAC in free running mode. // MR = Mode Register
  ADC->ADC_CR=2;         // Starts ADC conversion. // CR = Control Register 
  ADC->ADC_CHER=0xCC0;  // Enable ADC channels 0,1,8,9 and 10  //  1100 1100 0000 // CHER = Channel Enable Register
 
  //DAC Configuration
  analogWrite(DAC0,0);  // Enables DAC0
  analogWrite(DAC1,0);  // Enables DAC1
  
  //pedalSHIELD pin configuration
  pinMode(LED, OUTPUT);  
  pinMode(FOOTSWITCH, INPUT_PULLUP);      
  pinMode(TOGGLE, INPUT_PULLUP);  
  
}
 
void loop()

{
  
  //Read the ADCs
  while((ADC->ADC_ISR & 0xCC0)!=0xCC0);// wait for ADC 0,1,8,9 conversion complete. // ISR = Interrupt Status Register 
  in_ADC0=ADC->ADC_CDR[7];               // read data from ADC0 // CDR = Channel Data Register
  in_ADC1=ADC->ADC_CDR[6];               // read data from ADC1  
  Vol=ADC->ADC_CDR[10];                 // read data from ADC8        
  Drive=ADC->ADC_CDR[11];                 // read data from ADC9   
 


 
  //high_threshold=map(Drive,0,4095,4095,2047);
  //low_threshold=map(Drive,0,4095,0,2047);
   
  //s1_threshold=map(Drive,0,4095,2730,4095);
  //s2_threshold=map(Drive,0,4095,1365,2729);
  //s3_threshold=map(Drive,0,4095,0,1364); 

   //s1_threshold=map(Drive,0,4095,4095,2730);
  //s2_threshold=map(Drive,0,4095,2729,1365);
  //s3_threshold=map(Drive,0,4095,0,1364); 

  s4_threshold=map(in_ADC1,4095,2730,4095,4095);
  s5_threshold=map(in_ADC1,2729,1365,3000,1550);
  s6_threshold=map(in_ADC1,1364,0,0,2600);

   s1_threshold=map(in_ADC0,4095,2730,4095,4095);
  s2_threshold=map(in_ADC0,2729,1365,3000,1550);
  s3_threshold=map(in_ADC0,1364,0,2600,0);
  
  //if(in_ADC0>s3_threshold) 
   // in_ADC0=s3_threshold;
  //else if(in_ADC0<=s2_threshold)  
   // in_ADC0=s2_threshold;
  //else if(in_ADC0<= s1_threshold)  
    //in_ADC0=s1_threshold;

    //if(in_ADC1>s3_threshold) 
    //in_ADC1=s3_threshold;
  //else if(in_ADC1<=s2_threshold)  
    //in_ADC1=s2_threshold;
  //else if(in_ADC1<= s1_threshold)  
    //in_ADC1=s1_threshold;

   // if(0<=in_ADC1<=1364) 
    //in_ADC1=2*in_ADC1;
  //else if(1365<=in_ADC1<=2729)  
    //in_ADC1=1.3*in_ADC1;
  //else if(2730<=in_ADC1<=4095)  
    //in_ADC1=4095;
    // else if(in_ADC1<=s2_threshold)  
   // in_ADC0=2*in_ADC0;
//  else if(in_ADC0=s1_threshold)  
   // in_ADC0=2*in_ADC0;

  //if(in_ADC1>=s1_threshold) 
   // in_ADC1=4095;
   // else if(in_ADC1>=s2_threshold)  
  //  in_ADC1=1.3*in_ADC1;
 // else if(in_ADC1=s2_threshold)  
    //in_ADC1=1.3*in_ADC1;
   //  else if(in_ADC1<=s2_threshold)  
 //   in_ADC1=2*in_ADC1;
 // else if(in_ADC1=s1_threshold)  
   // in_ADC1=2*in_ADC1;

    
 
 
  //adjust the volume 
  out_DAC0=map((s4_threshold,s3_threshold,s6_threshold),0,4095,1,Vol);
  out_DAC1=map((s1_threshold,s2_threshold,s3_threshold),0,4095,1,Vol);
 
 
  //Write the DACs
  dacc_set_channel_selection(DACC_INTERFACE, 0);          //select DAC channel 0 // DACC = Digital-to-Analog Converter Controller 
  dacc_write_conversion_data(DACC_INTERFACE, out_DAC0);   //write on DAC
  dacc_set_channel_selection(DACC_INTERFACE, 1);          //select DAC channel 1
  dacc_write_conversion_data(DACC_INTERFACE, out_DAC1);   //write on DAC

  //Turn on the LED if the effect is ON.
  if (digitalRead(FOOTSWITCH)) digitalWrite(LED, HIGH); 
     else  digitalWrite(LED, LOW);
}
