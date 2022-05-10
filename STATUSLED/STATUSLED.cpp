#include "STATUSLED.h"


// make this instance available in the sketch
STATUSLED statusled;

STATUSLED::STATUSLED(void){}

NFCTAG_StatusTypeDef STATUSLED::ST25DV_i2c_ReadMBLength_Dyn(uint8_t *const pMBLength)
{
  /* Read actual value of MBLEN_DYN register */
  return ST25DV_i2c_ReadMailboxRegister(pMBLength, ST25DV_MB_LEN_DYN_REG, 1);
}

NFCTAG_StatusTypeDef STATUSLED::ST25DV_i2c_WriteMailboxRegister(const uint8_t *const pData, const uint16_t TarAddr, const uint16_t NbByte)
{
  NFCTAG_StatusTypeDef status;

  if ((TarAddr < ST25DV_GPO_DYN_REG) || (TarAddr > ST25DV_MB_LEN_DYN_REG)) {
    return NFCTAG_ERROR;
  }

  /* ST25DV can write a maximum of 256 bytes in Mailbox */
  if (NbByte < ST25DV_MAX_MAILBOX_LENGTH) {
    /* Write NbByte data in memory */
    status = ST25DV_IO_MemWrite(pData, ST25DV_ADDR_DATA_I2C, TarAddr, NbByte);
  } else {
    status = NFCTAG_ERROR;
  }

  return status;
}

NFCTAG_StatusTypeDef STATUSLED::ST25DV_i2c_ResetGPO_en_Dyn(void)
{
  uint8_t reg_value;
  NFCTAG_StatusTypeDef status;

  /* Read actual value of GPO_DYN register */
  status = ST25DV_i2c_ReadMailboxRegister(&reg_value, ST25DV_GPO_DYN_REG, 1);
  if (status != NFCTAG_OK) {
    return status;
  }

  /* Update GPO enable configuration */
  reg_value &= ST25DV_GPO_DYN_ENABLE_FIELD;

  /* Write GPO_DYN Register */
  return ST25DV_i2c_WriteMailboxRegister(&reg_value, ST25DV_GPO_DYN_REG, 1);
}

NFCTAG_StatusTypeDef STATUSLED::ST25DV_i2c_ReadGPO_Dyn(uint8_t *GPOConfig)
{
  /* Read actual value of ST25DV_GPO_DYN_REG register */
  return ST25DV_i2c_ReadMailboxRegister(GPOConfig, ST25DV_GPO_DYN_REG, 1);
}


NFCTAG_StatusTypeDef STATUSLED::ST25DV_i2c_GetRFField_Dyn(ST25DV_FIELD_STATUS *const pRF_Field)
{
  NFCTAG_StatusTypeDef status;
  uint8_t reg_value = 0;

  /* Read actual value of EH_CTRL_DYN register */
  status = ST25DV_i2c_ReadMailboxRegister(&reg_value, ST25DV_EH_CTRL_DYN_REG, 1);

  /* Extract RF Field information */
  if (status == NFCTAG_OK) {
    if ((reg_value & ST25DV_EH_CTRL_DYN_FIELD_ON_MASK) == ST25DV_EH_CTRL_DYN_FIELD_ON_MASK) {
      *pRF_Field = ST25DV_FIELD_ON;
    } else {
      *pRF_Field = ST25DV_FIELD_OFF;
    }
    return NFCTAG_OK;
  }

  return status;
}


NFCTAG_StatusTypeDef STATUSLED::ST25DV_i2c_ReadMailboxRegister(uint8_t *const pData, const uint16_t TarAddr, const uint16_t NbByte)
{
  if ((TarAddr < ST25DV_GPO_DYN_REG) || (TarAddr > ST25DV_MB_LEN_DYN_REG)) {
    return NFCTAG_ERROR;
  }

  return ST25DV_IO_MemRead(pData, ST25DV_ADDR_DATA_I2C, TarAddr, NbByte);
}
