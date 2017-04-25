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

typedef enum ICV_CLI_CMD
{
    ICV_CLI_SNR                   = 0x0,
    ICV_CLI_QLN                   = 0x1,
    ICV_CLI_GAINALLOC,
    ICV_CLI_HLOG,
    ICV_CLI_LINIMG,
    ICV_CLI_LINREAL,
    ICV_CLI_BITLOAD
};

#define ICV_DATA_SCOPE_BCM    (0)
#define ICV_DATA_SCOPE_CLI    (1)
#define RFC_HLOG_CONV(a)      (6 - (a)/10.0)
#define RFC_QLN_CONV(a)       (-23 - (a)/2.0)
#define RFC_SNR_CONV(a)       (-32 + (a)/2.0)
#define RFC_GAIN_CONV(a)      ((a)/512.0)

#endif

