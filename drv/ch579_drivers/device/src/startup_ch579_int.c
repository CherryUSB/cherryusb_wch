#include "CH57x_clk.h"

extern int main(void);
extern unsigned int _lvmdata, _sdata, _edata, _sbss, _ebss;

void _copydata(unsigned int *form, unsigned int *section_begin, unsigned int *section_end)
{
  unsigned int *p = section_begin;
  while (p < section_end)
  {
    *(p++) = *(form++);
  }
}

void _bssinit(unsigned int *startbss, unsigned int *endbss)
{
  unsigned int *p = startbss;
  while (p < endbss)
  {
    *(p++) = 0;
  }
}

void Reset_Handler(void)
{
  _bssinit(&_sbss, &_ebss);
  _copydata(&_lvmdata, &_sdata, &_edata);
  SystemInit();
  main();
}
void NMI_Handler(void)
{
  while (1)
    ;
}
void HardFault_Handler(void)
{
  while (1)
    ;
}
void SVC_Handler(void)
{
  while (1)
    ;
}
void PendSV_Handler(void)
{
  while (1)
    ;
}
void SysTick_Handler(void)
{
}