// This #include statement was automatically added by the Spark IDE.
#import <math.h>


/*****************************************************************************
Uses PWM to drive RGB LED strips.  Needs a power stage to drive LEDs.

Copywrite Matt Lovett 2015
*****************************************************************************/


int redRand = 0;
int greenRand = 255;
int blueRand = 128; 
int RedPoint = 0;
int BluePoint = 128;
int GreenPoint = 255;
int RedDiff;
int GreenDiff;
int BlueDiff;
int loop_count = 0;
bool hold_color = false;
int coeff;
int rval;
int gval;
int bval;
int mode = 1;

int ledRed = A6;
int ledGreen= A7;
int ledBlue = A5;

// This routine runs only once upon reset
void setup(){
    // Configure the pins to be outputs
    pinMode(ledRed, OUTPUT);
    pinMode(ledGreen, OUTPUT);
    pinMode(ledBlue, OUTPUT);

    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledBlue, HIGH);
    
    Spark.function("alarm", alarm);
    Spark.function("hold", hold);
    Spark.function("fade", fade);

}

void loop(){
    
    if( RedPoint == redRand && BluePoint == blueRand && RedPoint == redRand){
        int redMode = rand() % 5;
         switch (redMode) {
            case 1:
                redRand = rand() % 255;
                break;
            case 2:
                redRand = 0;
                break;
            default: 
                int RedRange = (RedPoint * .33);
                do {
                    redRand = rand() % 255;
                    RedDiff = abs( redRand - RedPoint);
                } while (RedDiff < RedRange);
          }
        int blueMode = rand() % 5;
        switch (blueMode) {
            case 1:
                blueRand = rand() % 255;
                break;
            case 2:
                blueRand = 0;
                break;
            default: 
                int BlueRange = (BluePoint * .33);
                do {
                    blueRand = rand() % 255;
                    BlueDiff = abs( blueRand - BluePoint);
                }while (BlueDiff < BlueRange);
        }
        int greenMode = rand() % 5;
        switch (greenMode) {
            case 1:
                greenRand = rand() % 255;
                break;
            case 2:
                greenRand = 0;
                break;
            default: 
                int GreenRange = (GreenPoint * .33);
                do {
                    greenRand = rand() % 255;
                    GreenDiff = abs( greenRand - GreenPoint);
                }while (GreenDiff < GreenRange);
        }
        
        
        
        String color = String(String(redRand) + " " + String(greenRand) + " " + String(blueRand));
        Spark.publish("HOMEr", color);

     
    }
    
    
    if (!hold_color){   
        if (millis()-loop_count > 500){
            
            if (RedPoint != redRand){
                if ( RedPoint < redRand){
                    RedPoint ++;
                }
                if (RedPoint > redRand){
                    RedPoint --;
                }
                coeff = pow((double)RedPoint / 255, 2.5) * 255 + 0.5 ;
                rval = abs(coeff);
            }
              
            if (BluePoint != blueRand){
                if ( BluePoint < blueRand){
                  BluePoint ++;
                } 
                if (BluePoint > blueRand){
                  BluePoint --;
                }
                coeff = pow((double)BluePoint / 255, 2.5) * 255 + 0.5;
                bval = abs(coeff);
            }
              
            if (GreenPoint != greenRand){
                if ( GreenPoint < greenRand){
                   GreenPoint ++;
                }
                if (GreenPoint > greenRand){
                   GreenPoint --;
                }
                coeff = pow((double)GreenPoint / 255, 2.5) * 255 + 0.5;
                gval = abs(coeff);
            }
            //String color = String(String(255-rval) + " " + String(255-gval) + " " + String(255-bval));
            //Spark.publish("Sperryfreak01", color);
    
            analogWrite(ledRed, 255-rval);
            analogWrite(ledGreen, 255-gval);
            analogWrite(ledBlue, 255-bval);
            //Spark.publish("Green", String(gval));
            //Spark.publish("Blue", String(bval));
            //Spark.publish("Red", String(rval));
            loop_count = millis();
    
        }
    }
}


int hold(String command){
     
    String rval = command.substring(0,3);
    String gval = command.substring(4,7);
    String bval = command.substring(8,11);
    
    hold_color = 1;
    //uint32_t RGB1 = Color(rval.toInt(), gval.toInt(), bval.toInt());
    analogWrite(ledRed, 255-rval.toInt());
    analogWrite(ledGreen, 255-gval.toInt());
    analogWrite(ledBlue, 255-bval.toInt());
    return 1;
}  

int fade(String command){
    hold_color = 0;
    return 1;
}  


int alarm(String command){
    
    String rval = command.substring(0,3);
    String gval = command.substring(4,7);
    String bval = command.substring(8,11);

    //uint32_t RGB = Color(rval.toInt(), gval.toInt(), bval.toInt());
    for (int i = 0; i < 5; i++){
    
        analogWrite(ledRed, 255);
        analogWrite(ledGreen, 255);
        analogWrite(ledBlue, 255);
        delay(500);
        analogWrite(ledRed, 255-rval.toInt());
        analogWrite(ledGreen, 255-gval.toInt());
        analogWrite(ledBlue, 255-bval.toInt());
        delay(500);
        
    }
    
    return 1;
}
