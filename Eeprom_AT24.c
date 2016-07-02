/***************************************************************************

         EERPOM��ȡλ�ñ�׼���ӿ�-��24ϵ���е�ʵ��
//ͨ������,֧�ִ�24C01~24C512�е���������(����оƬδ����!!!!)
//ʹ��I2c��׼�ӿڵ�����), ��Բ�ͬ��24ϵ��,ֻ���������ü���ʵ��
***************************************************************************/

/***************************************************************************
                        �û�����˵��
//����Ԥ�����и�������˵��������,(24x�е�xָ��ͬϵ��)
***************************************************************************/
//��Ե�ǰ��Ŀ֧�ֵ�оƬ,���붨�������е�һ��
//#define SUPPORT_AT24x01
//#define SUPPORT_AT24x02
//#define SUPPORT_AT24x04
//#define SUPPORT_AT24x08
//#define SUPPORT_AT24x16
//#define SUPPORT_AT24x32
//#define SUPPORT_AT24x64
//#define SUPPORT_AT24x128
//#define SUPPORT_AT24x256
//#define SUPPORT_AT24x512

//ָ��ʹ������I2CӲ���豸,Ĭ�Ϸ���I2c.h��� (&I2c.I2cDev0)
//�����,����Eeprom_AT24_Pri.h��ʵ��:Eeprom_At24_pGetI2cDev()
//#define AT24_OTHER_I2C_DEV

//�ӵ�Ӳ����ַA0,A1,A2,������ʱ��ʾȫ���ӵ�,�����趨��Ϊ1~7
//#define AT24_HW_ADR

//I2CͨѶʱ�ĵȴ�ʱ��,��ʱͨ������,I2c_Task()��������Ϊ��λ,��������Ϊ10
//#define AT24_WAIT_OV

//I2CдEeprom����ʱ,�ȴ�ʱ��,ֱ�ӵ���ϵͳӲ����ʱ
//Ĭ��ʹ��Delay.h�е�DelayMs(), ʱ��Ϊ100mS
//�����,����Eeprom_AT24_Pri.h��ʵ��:Eeprom_At24_pGetWrDelay()
//#define AT24_OTHER_WR_DELAY

signed char Eeprom_Err = 0;  //��ʶ���һ������д����
//�ⲿ��Ҫ����ʱ,������Eeprom_AT24_Pri.h��ʵ������

/***************************************************************************
                             �ڲ���ת��
***************************************************************************/

#ifndef AT24_HW_ADR
  #define AT24_HW_ADR  0 //���ӵ�Ӳ����ַA0,A1,A2,Ĭ��ȫ���ӵ�,�����趨��
#endif

#ifndef AT24_WAIT_OV
  #define AT24_WAIT_OV  10
#endif

#ifndef AT24_OTHER_I2C_DEV
  #include "I2c.h"
  #define       Eeprom_pGetI2cDev()      (&I2c.I2cDev[0])
#else
  #include "Eeprom_AT24_Pri.h.h" //�û�����ʵ��
#endif 

#ifndef AT24_OTHER_WR_DELAY
  #include "Delay.h"
  #define Eeprom_cbDelayWr() do{DelayMs(100);}while(0)
#else
  #include "Eeprom_AT24_Pri.h.h" //�û�����ʵ��
#endif 

/***************************************************************************
                 �ڲ���ת��-��Բ�ͬоƬ����
***************************************************************************/
#ifdef SUPPORT_AT24x01
  #define _CMD_BUF_SIZE    1   //�����ֳ�
  #define _GetI2cAdr(adr)     ((0xA0 | AT24_HW_ADR) >> 1)   //Ӳ����ַA0,A1,A2
  #define _GetBlockSize()  8   //һ���Կɶ�ȡ�����鳤��
#endif

#ifdef SUPPORT_AT24x02
  #define _CMD_BUF_SIZE    1   //�����ֳ�
  #define _GetI2cAdr(adr)     ((0xA0 | AT24_HW_ADR) >> 1)   //Ӳ����ַA0,A1,A2
  #define _GetBlockSize()  16  //һ���Կɶ�ȡ�����鳤��
#endif

#ifdef SUPPORT_AT24x04
  #define _CMD_BUF_SIZE    1   //�����ֳ�
  #define _GetI2cAdr(adr)  ((0xA0 | AT24_HW_ADR | (((adr) >> 8) & 0x01))\
                            >> 1)   //Ӳ����ַA1,A2
  #define _GetBlockSize()  16  //һ���Կɶ�ȡ�����鳤��
#endif

#ifdef SUPPORT_AT24x08
  #define _CMD_BUF_SIZE    1   //�����ֳ�
  #define _GetI2cAdr(adr)  ((0xA0 | AT24_HW_ADR | (((adr) >> 8) & 0x03))\
                            >> 1)   //Ӳ����ַA2
  #define _GetBlockSize()  16  //һ���Կɶ�ȡ�����鳤��
#endif

#ifdef SUPPORT_AT24x16
  #define _CMD_BUF_SIZE    1   //�����ֳ�
  #define _GetI2cAdr(adr)  ((0xA0 | (((adr) >> 8) & 0x07)) >> 1)   //��Ӳ����ַ
  #define _GetBlockSize()  16  //һ���Կɶ�ȡ�����鳤��
#endif

#ifdef SUPPORT_AT24x32
  #define _CMD_BUF_SIZE    2   //�����ֳ�
  #define _GetI2cAdr(adr)     ((0xA0 | AT24_HW_ADR) >> 1)   //Ӳ����ַA0,A1,A2
  #define _GetBlockSize()  32   //һ���Կɶ�ȡ�����鳤��
#endif

#ifdef SUPPORT_AT24x64
  #define _CMD_BUF_SIZE    2   //�����ֳ�
  #define _GetI2cAdr(adr)     ((0xA0 | AT24_HW_ADR) >> 1)   //Ӳ����ַA0,A1,A2
  #define _GetBlockSize()  32   //һ���Կɶ�ȡ�����鳤��
#endif

#ifdef SUPPORT_AT24x128
  #define _CMD_BUF_SIZE    2   //�����ֳ�
  #define _GetI2cAdr(adr)     ((0xA0 | AT24_HW_ADR) >> 1)   //Ӳ����ַA0,A1,A2
  #define _GetBlockSize()  64   //һ���Կɶ�ȡ�����鳤��
#endif

#ifdef SUPPORT_AT24x256
  #define _CMD_BUF_SIZE    2   //�����ֳ�
  #define _GetI2cAdr(adr)     ((0xA0 | AT24_HW_ADR) >> 1)   //Ӳ����ַA0,A1
  #define _GetBlockSize()  64   //һ���Կɶ�ȡ�����鳤��
#endif

#ifdef SUPPORT_AT24x512
  #define _CMD_BUF_SIZE    2   //�����ֳ�
  #define _GetI2cAdr(adr)     ((0xA0 | AT24_HW_ADR) >> 1)   //Ӳ����ַA0,A1
  #define _GetBlockSize()  128  //һ���Կɶ�ȡ�����鳤��
#endif

//#ifdef SUPPORT_AT24x1024 ->��洢λ�ö���û��������,���ݲ��ṩ֧��
//  #define _CMD_BUF_SIZE    2   //�����ֳ�
//  #define _GetI2cAdr(adr)     ((0xA0 | AT24_HW_ADR) >> 1)   //Ӳ����ַA1
//  #define _GetBlockSize()  128  //һ���Կɶ�ȡ�����鳤��
//#endif

/***************************************************************************
                           ��غ���ʵ��
***************************************************************************/

#include "Eeprom.h"
#include "I2cDev.h"   //�����ڸ�����֮��
#include <string.h>

static I2cData_t Eeprom_I2cData;       //����һ��ʵ��������
static unsigned char Eeprom_CmdBuf[_CMD_BUF_SIZE];//�̶����������

//-----------------------------��ʼ������---------------------------------
void Eeprom_Init(void)
{
  //memset(&Eeprom_I2cData,0,sizeof(I2cData_t));
  //�����Ԥ��ʼ��һֱ���ֲ���Ĳ���:
  Eeprom_I2cData.CmdSize = _CMD_BUF_SIZE;    //ͨѶ�����б��̶ֹ�
  Eeprom_I2cData.pCmd = Eeprom_CmdBuf;
}

//---------------------------��ȡEeprom����---------------------------------
void Eeprom_Rd(EepromAdr_t Adr,   //Eerpom�еĴ�ȡλ��
               void *pVoid,       //�������ݵ���ʼλ��
               EepromLen_t Len)  //��ȡ����
{
  Eeprom_I2cData.Flag = I2C_CMD_RD | AT24_WAIT_OV;
  unsigned char *pByteData = (unsigned char *)pVoid;
  unsigned char CurSize;

  Eeprom_Err = 0; //Ԥ����ȷ
  
  //��I2C�������������������Ϊ255,����������
  while(Len){
    //�ж����Ҫ���ֽ���
    if(Len < 255)CurSize = Len;//�жϵ�ַ�Ƿ�Խ��ҳд������ַ
    else CurSize = 255;

    Eeprom_I2cData.DataSize = CurSize;
    Eeprom_I2cData.pData = pByteData;
    Eeprom_I2cData.SlvAdr = _GetI2cAdr(Adr);  
    #if _CMD_BUF_SIZE > 1
      Eeprom_CmdBuf[1] = (unsigned char)Adr;//��8λ��ַ
      Eeprom_CmdBuf[0] = (unsigned char)(Adr >> 8);//��8λ��ַ
    #else
      Eeprom_CmdBuf[0] = (unsigned char)Adr;//��8λ��ַ
    #endif
    //Eeprom_I2cData.pCmd = &Eeprom_CmdBuf[0]; //�ҽ�����

    I2cDev_ReStart(Eeprom_pGetI2cDev(),&Eeprom_I2cData);
    while(!I2cDev_IsEnd(Eeprom_pGetI2cDev()));
    //���ϴ���
    if(I2cDev_eGetSatate(Eeprom_pGetI2cDev()) != eI2cDone)
      Eeprom_Err = -1;
    //��һ����
    Len -= CurSize;
    Adr += CurSize;
    pByteData += CurSize;
    //���￴�Ź�����
  }
}

//---------------------------д��Eeprom����---------------------------------
void Eeprom_Wr(EepromAdr_t Adr,   //Eerpom�еĴ�ȡλ��
               const void *pVoid, //��д���ݵ���ʼλ��
               EepromLen_t Len)   //д�볤��
{
  Eeprom_I2cData.Flag = I2C_CMD_WR | AT24_WAIT_OV;
  unsigned char *pByteData = (unsigned char *)pVoid;
  unsigned short i;
  unsigned char CurSize;
  
  Eeprom_Err = 0; //Ԥ����ȷ
  
  //������д
  while(Len){
    //�ж����Ҫд�ֽ���
    i = _GetBlockSize() - (Adr % _GetBlockSize());
    if(Len < i)CurSize = Len;//�жϵ�ַ�Ƿ�Խ��ҳд������ַ
    else
      CurSize = i;

    Eeprom_I2cData.DataSize = CurSize;
    Eeprom_I2cData.pData = pByteData;
    Eeprom_I2cData.SlvAdr = _GetI2cAdr(Adr);  
    #if _CMD_BUF_SIZE > 1
      Eeprom_CmdBuf[1] = (unsigned char)Adr;//��8λ��ַ
      Eeprom_CmdBuf[0] = (unsigned char)(Adr >> 8);//��8λ��ַ
    #else
      Eeprom_CmdBuf[0] = (unsigned char)Adr;//��8λ��ַ
    #endif
    //Eeprom_I2cData.pCmd = &Eeprom_CmdBuf[0]; //�ҽ�����

    I2cDev_ReStart(Eeprom_pGetI2cDev(),&Eeprom_I2cData);
    while(!I2cDev_IsEnd(Eeprom_pGetI2cDev()));
    Eeprom_cbDelayWr();//д��ʱ
    //���ϴ���
    if(I2cDev_eGetSatate(Eeprom_pGetI2cDev()) != eI2cDone)
      Eeprom_Err = -1;
    //��һ����
    Len -= CurSize;
    Adr += CurSize;
    pByteData += CurSize;
    //���￴�Ź�����
  }
  Eeprom_Err = 0;
}

//--------------------------Eepromд��������--------------------------
//�˺���Ϊ���ӹ���, ��������ʵ��
void Eeprom_WrConst(EepromAdr_t Adr,   //Eerpom�еĴ�ȡλ��
                  unsigned char Data,         //��������
                  EepromLen_t Len)            //д�볤��
{
  unsigned short CurSize;
  static unsigned char DataBuf[_GetBlockSize()];
  memset(DataBuf, Data, _GetBlockSize());
  do{
    if(Len > _GetBlockSize()) CurSize = _GetBlockSize();
    else CurSize = Len;
    Eeprom_Wr(Adr,DataBuf,CurSize);
    Len -= CurSize;
    Adr += CurSize;
  }while(Len);
}
