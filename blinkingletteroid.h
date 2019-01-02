#ifndef _BLINKINGLETTEROID_H_
#define _BLINKINGLETTEROID_H_

#include "letteroid.h"

class BlinkingLetteroid :public Letteroid {
 public:
  BlinkingLetteroid(bool data=true) {m_DrawIt=data;}
  void blink();
  
 private:
  bool m_DrawIt;
  
};




#endif
