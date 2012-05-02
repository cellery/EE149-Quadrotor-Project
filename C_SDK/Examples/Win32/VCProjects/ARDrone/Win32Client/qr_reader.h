#ifndef QR_READER_H
#define QR_READER_H
#include "VP_Os/vp_os_types.h"
#include "VP_Os/vp_os_signal.h"

#ifdef __cplusplus
extern "C" {
#endif
int scan_qr(int width, int height, uint8_t * raw, char * strs);
#ifdef __cplusplus
}
#endif
#endif