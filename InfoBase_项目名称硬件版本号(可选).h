/***************************************************************************

             EERPOM��ȡλ�ñ�׼��-����Ӧ��ʵ��ģ��

***************************************************************************/
#ifndef __INFO_��Ŀ����_Ӳ���汾��(��ѡ)_H 
#define __INFO_��Ŀ����_Ӳ���汾��(��ѡ)_H 

/**********************************************************************
                       ��ģ��洢����
**********************************************************************/

//UvSensorģ��
struct _UvSensorInfoIni{
  unsigned char Reserved[8];//Ԥ���ռ�
};

//DA_Adjģ��
struct _DA_AdjInfoIni{
  unsigned char Reserved[4];//Ԥ���ռ�
};

//ModbusRtuMngģ��
struct _ModbusRtuMngInfoIni{
  unsigned char Reserved[8];//Ԥ���ռ�
};

/**********************************************************************
                        ��Ϣ���ṹ����
**********************************************************************/
typedef struct _InfoBase{
   //0ַ�̶�Ϊ��ʼ����־,Ϊ0x5aʱ��ʾ�ѳ�ʼ��,����ʱΪδʹ��
  unsigned char InitedFlag;
  struct _UvSensorInfoIni UvSensorInfoIni;
  struct _DA_AdjInfoIni DA_AdjInfoIni;
  struct _ModbusRtuMngInfoIni ModbusRtuMngInfoIni;
  
}InfoBase_t;

/**********************************************************************
                        ��ػ�ַ������
**********************************************************************/
//InfoBase��ʼ����־
#define InfoBase_GetInitedFlagBase() struct_offset(InfoBase_t,InitedFlag)

//UvSensorģ��
#define UvSensor_GetInfoBase()  struct_offset(InfoBase_t, UvSensorInfoIni)

//DA_Adjģ��
#define DA_Adj_GetInfoBase()  struct_offset(InfoBase_t, DA_AdjInfoIni)

//ModbusRtuMngģ��
#define ModbusRtuMng_GetInfoBase()  struct_offset(InfoBase_t, ModbusRtuMngInfoIni)


#endif //#define __INFO_��Ŀ����_Ӳ���汾��(��ѡ)_H 


