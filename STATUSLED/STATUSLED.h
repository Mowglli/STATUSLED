#ifndef _STATUSLED_H_
#define _STATUSLED_H_

#include "ST25DVSensor.h"
#include "BSP/x_nucleo_nfc04a1.h"
#include "Arduino.h"
#include "RDMmaster.h"
#include "NFC.h"

#define ST25DV_MB_LEN_DYN_REG                 0x2007

class STATUSLED: public ST25DV{
  public:
    STATUSLED(void);
    NFCTAG_StatusTypeDef ST25DV_i2c_ReadMBLength_Dyn(uint8_t *const pMBLength);
    NFCTAG_StatusTypeDef ST25DV_i2c_WriteMailboxRegister(const uint8_t *const pData, const uint16_t TarAddr, const uint16_t NbByte);
    NFCTAG_StatusTypeDef ST25DV_i2c_ResetGPO_en_Dyn(void);
    NFCTAG_StatusTypeDef ST25DV_i2c_ReadGPO_Dyn(uint8_t *GPOConfig);
    NFCTAG_StatusTypeDef ST25DV_i2c_GetRFField_Dyn(ST25DV_FIELD_STATUS *const pRF_Field);
    NFCTAG_StatusTypeDef ST25DV_i2c_ReadMailboxRegister(uint8_t *const pData, const uint16_t TarAddr, const uint16_t NbByte);
};

extern STATUSLED statusled;

#endif
