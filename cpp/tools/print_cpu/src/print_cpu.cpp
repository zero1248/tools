/*
 * @Author: gaoy
 * @Date: 2022-07-15 14:09:03
 * @LastEditors: gaoy
 * @LastEditTime: 2022-07-15 14:36:23
 * @Description: file content
 */

#include "print_cpu.h"
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include "cpuid1.h"



// char* get_cpu_info() {
//     char* cpu_info = new char[100];
//     FILE* fp = fopen("/proc/cpuinfo", "r");
//     if (fp == NULL) {
//         return NULL;
//     }
//     while (!feof(fp)) {
//         fgets(cpu_info, 100, fp);
//         if (strstr(cpu_info, "model name") != NULL) {
//             break;
//         }
//     }
//     fclose(fp);
//     return cpu_info;
// }

char* cpu_brand_string(void) {

    uint32_t mx[4], i, a, b, c, d;

    #if (defined(__i386__) || defined(__x86_64__))
    char* cpu_brand_str = (char*)calloc(1, 3*sizeof(mx)+1);
    if (!cpu_brand_str)
        return NULL;
    __cpuid(CPUID_EXTENDED, a, b, c, d); // check availability of extended functions
    if (a >= CPUID_BRANDSTRINGEND) {
        for(i=0; i<=2; i++) {
            cpuid_string(CPUID_BRANDSTRING+i, (uint32_t*)mx);
            strncpy(cpu_brand_str+sizeof(mx)*i, (char*)mx, (3-i)*sizeof(mx)+1);
        }	
	}
		
    else
        return NULL; // CPUID_EXTENDED unsupported by cpu

    cpu_brand_str[3*sizeof(mx)+1] = '\0';
    return cpu_brand_str;
    #else
    return NULL;
    #endif // (defined(__i386__) || defined(__x86_64__))
}



