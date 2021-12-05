#include <iostream>
#include <mutex>
#include "RingBuffCAN.h"

int main()
{
    RingBufferForCAN rbb(100);

    int ret;
    for (unsigned int i = 0; i < 2 * rbb.GetBufferSize(); i++) {
        canData testData = { "message", "EDP" };
        ret = rbb.WriteBuffer(testData);
        if (ret != 0) {
            printf("書きこみエラー i=%u", i);
            break;
        }
    }

    return 0;
}
