
#include <iostream>
#include <zbar.h>
#include <zbar/Image.h>
#include "VP_Os/vp_os_types.h"
#include "qr_reader.h"
using namespace std;
using namespace zbar;


extern "C" char string_buffers[8][4296];
extern "C" vp_os_mutex_t qr_update_lock;
extern "C" int qr_count;

extern "C" int scan_qr(int width, int height, uint8_t * raw, char * strs) {
	ImageScanner scanner;

    // configure the reader
    scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);
    Image image(width, height, "Y800", raw, width * height);
	
	int n = scanner.scan(image);

	int i = 0;
	
	vp_os_mutex_lock(&qr_update_lock);

    for(Image::SymbolIterator symbol = image.symbol_begin();
        symbol != image.symbol_end();
        ++symbol) {
		strncpy( strs+(i*4296), symbol->get_data().c_str(),4296);
		i++;

		//MAX OF 8 QR CODES.
		if (i == 8) {break;}
    }
	qr_count = n;
	vp_os_mutex_unlock(&qr_update_lock);
	return n;
}