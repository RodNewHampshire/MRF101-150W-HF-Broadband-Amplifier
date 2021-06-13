#ifndef Mrf_R_LCD_h
#define Mrf_R_LCD_h

class Mrf_R_LCD
{
  public:
  	Mrf_R_LCD(void);
  	void begin(void);
  	void clear(void);
  	void splash(void);
  	void initializeDisplay(void);
    void updateStatusDisplay(uint8_t);
    void updateAmpDisplay(float);
    void UpdateBandDisplay(uint8_t);
  	
  private:
	void updateAmpBars(uint8_t);
};

#endif