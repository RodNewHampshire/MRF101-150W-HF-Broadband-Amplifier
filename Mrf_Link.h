#ifndef Mrf_Link_h
#define Mrf_Link_h


class Mrf_Link
{
  public:
  	Mrf_Link(void);
    void begin(void);
    bool available(void);
    void getBand(void);
    uint8_t trStatus(void);

  private:
    void updateBand(void);
    void updateTRStatus(void);
    void send(uint8_t data[], uint8_t num);
    void execute(void);
};


#endif