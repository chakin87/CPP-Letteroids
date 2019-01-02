#include "blinkingletteroid.h"

void BlinkingLetteroid::blink() {
    if (m_DrawIt == true) 
    {
      draw(); /// in the base class
      m_DrawIt = false;
    }
    else 
    { 
      erase(); /// in the base case
      m_DrawIt = true;
    }
}
