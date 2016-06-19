/***************************************************************************

         EERPOM��ȡλ�ñ�׼���ӿ�-��PIC�ڲ�EEPROM�е�ʵ��

�˽ӿ�Ϊ������Ŀ: ���д�ȡλ�õ�,�ṩͳһ�ӿڡ�ʵ���˵��ò����ƶ�Ӧ�õķ��롣
***************************************************************************/

#include <pic.h>
#include "PicBit.h"

#include "Eeprom.h"

//---------------------------��ȡEeprom����---------------------------------
void Eeprom_Rd(EepromAdr_t Adr,
               void *pVoid,
               EepromLen_t Len)
{
    unsigned char *pData;
    pData = (unsigned char*)pVoid;
    for(;Len > 0; Len-- ,Adr++, pData++)
    {
        _CLI();                  //��֤�˴ζ����
        EEADRL = Adr;
        EECON1 &= ~PICB_CFGS;       //Deselect Config space and 
        EECON1 &= ~PICB_EEPGD;      //Point to DATA memory
        EECON1 |= PICB_RD;          //EE Read
        *pData = EEDATL;
        _SEI();
    }    
}

//---------------------------д��Eeprom����---------------------------------
void Eeprom_Wr(EepromAdr_t Adr,
               const void *pVoid,
               EepromLen_t Len)
{
    unsigned char *pData;
    pData = (unsigned char*)(pVoid);
    for(;Len > 0; Len--, Adr++, pData++)
    {
        EEADRL = Adr;
        EEDATL = *pData;
        _CLI();                  //��֤�˴ζ����
        EECON1 &= ~PICB_CFGS;       //Deselect Config space and 
        EECON1 &= ~PICB_EEPGD;      //Point to DATA memory
        EECON1 |= PICB_WREN; //��ʼд
        EECON2 = 0x55;
        EECON2 = 0xaa;
        EECON1 |= PICB_WR;   //����д����
        EECON1 &= ~PICB_WREN; //����д,��д�������ڼ���
        _SEI();
        while(EECON1 & PICB_WR){}; //�ȴ�д����
    }    
}




