/***************************************************************************

         EERPOM��ȡλ�ñ�׼���ӿ�-��AVR�ڲ�EEPROM�е�ʵ��

�˽ӿ�Ϊ������Ŀ: ���д�ȡλ�õ�,�ṩͳһ�ӿڡ�ʵ���˵��ò����ƶ�Ӧ�õķ��롣
***************************************************************************/

#include "Eeprom.h"

//#include <avr_macros.h>
#include <intrinsics.h>//interrupt_en
#include <comp_a90.h>//sei()
#include <ioavr.h>

//------------------------�Ĵ���˵������ز�����----------------------------
//EEAR  ��ַ�Ĵ���
//EEDR  ���ݼĴ���

//���ƼĴ���EECRλ����
#define EECR_EERIE   0x08    //E2�����ж�ʹ��
#define EECR_EEMWE   0x04    //дʹ��
#define EECR_EEWE    0x02    //дʹ��
#define EECR_EERE    0x01    //��ʹ��

#define _BusyWait()  do{ }while(EECR & EECR_EEWE)
#define _WriteIn()   do{\
  _CLI();\
  EECR = 0x04;\
  EECR = 0x06;\
  _SEI();\
}while(0)


//-----------------------------��ʼ������---------------------------------
void Eeprom_Init(void)
{

}

//---------------------------��ȡEeprom����---------------------------------
void Eeprom_Rd(EepromAdr_t Adr,
               void *pVoid,
               EepromLen_t Len)
{
  unsigned char *pData;
  pData = (unsigned char*)pVoid;
  for(; Len > 0; Len--, Adr++, pData++){
    _BusyWait();
    _CLI();                  //�ٽ�������
    EEAR = Adr;
    EECR = EECR_EERE;
    *pData = EEDR;
    _SEI();
  }    
}

//---------------------------д��Eeprom����---------------------------------
void Eeprom_Wr(EepromAdr_t Adr,
               const void *pVoid,
               EepromLen_t Len)
{
  const unsigned char *pData;
  pData = (const unsigned char*)(pVoid);
  for(; Len > 0; Len--, Adr++, pData++){
    _BusyWait();
    EEAR = Adr;
    EEDR = *pData;
    _WriteIn();
  }    
}


