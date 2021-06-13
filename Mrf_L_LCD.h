#ifndef Mrf_L_LCD_h
#define Mrf_L_LCD_h

class Mrf_L_LCD
{
  public:
  	Mrf_L_LCD(void);
  	void begin(void);
  	void clear(void);
  	void splash(void);
  	void initializeDisplay(void);
  	void updateTempDisplay(void);
    bool readADC(void);
    void initializeACS723(void);
  	
  private:
  uint8_t getBars(float);
  void updateTempBars(uint8_t, uint8_t);
  
};

#endif