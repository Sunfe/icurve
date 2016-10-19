#ifndef ICURVE_COMMON_H
#define ICURVE_COMMON_H

typedef enum STATUS
{
  ICU_OK                      = 0x0,
  ICU_PLOT_DATA_FORMAT_ERROR  = 0x1,
  ICU_FILE_NOT_EXIST          = 0X2,
  ICU_FILE_READ_ERROR         = 0X3,
  ICU_ERROR                   = 0xFF
}ICU_RET_STATUS;

#endif

