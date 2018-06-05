    #include <avr/sleep.h>
    
    int contacto = 9;
    int led= 8; 
    
    void wake ()
    {
      // cancel sleep as a precaution
      sleep_disable();
      // precautionary while we do other stuff
      detachInterrupt (0);
    }  // end of wake
    
    void setup () 
      {
      digitalWrite (2, HIGH);  // enable pull-up
          // end of setup
    
    
      pinMode(contacto,INPUT);
      pinMode(led, OUTPUT); 
      ADCSRA = 0;  
      set_sleep_mode (SLEEP_MODE_PWR_DOWN);  
      sleep_enable();
      attachInterrupt (contacto, wake, RISING);
      EIFR = bit (INTF0);  
        MCUCR = bit (BODS) | bit (BODSE);
        MCUCR = bit (BODS); 
        interrupts ();  
      sleep_cpu ();   
    }
    
    void loop(){
      if (digitalRead(contacto)==HIGH){
      
          digitalWrite(led,HIGH);  
      }else{
        digitalWrite(led,LOW); 
      }
    }

