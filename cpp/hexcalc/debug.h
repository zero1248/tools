#ifndef _DEBUG_H_
#define _DEBUG_H_

#define USER_SPACE

#ifdef USER_SPACE
#include <cstdio>
#else
#endif

#ifdef USER_SPACE
#define PRINT printf
#else
#define PRINT printk
#endif

#ifndef TARGET_NAME
#define TARGET_NAME
#endif

#define _print_level(name)  print_level_##name
#define print_level(name)   _print_level(name)

#define _str(name)  #name
#define str(name)   _str(name)

extern int print_level(TARGET_NAME);

/* 颜色设置 */
#define GREEN       "\033[40;32m"
#define YELLOW      "\033[40;33m"
#define PURPLE      "\033[40;35m"
#define RED         "\033[40;31m"
#define RESET       "\033[0m"

/* 
 * debug level,
 * PRINT_LEVEL_DISABLE  --   禁止打印调试信息
 * PRINT_LEVEL_NOTICE   --   打印关键调试信息 
 * PRINT_LEVEL_DEBUG    --   打印所有DEBUG/NOTICE调试信息
 * ALERT/INFO           --   无法屏蔽ALERT/INFO信息
 */

enum level {
    PRINT_LEVEL_DISABLE = 0,
    PRINT_LEVEL_NOTICE,
    PRINT_LEVEL_DEBUG
};

#define set_print_level(level)  do{print_level(TARGET_NAME) = level;}while(0)

/*
 *  alert   --  用于打印错误信息，不可屏蔽
 *  info    --  用于打印基础信息，不可屏蔽
 *  notice  --  用于打印关键调试信息，可屏蔽
 *  debug   --  用于打印全部调试信息，可屏蔽
 */

#define ERR(fmt,args...)                                                                   	\
    do{                                                                                    	\
         PRINT("[" RED "Error" RESET "]""[%s][%s][%d]"fmt, str(TARGET_NAME), __FUNCTION__, __LINE__, ##args);    	\
    }while(0)               

#define INFO(fmt,args...)                                                                   \
    do{                                                                                    	\
        PRINT("[" PURPLE "Info" RESET "]""[%s][%s][%d]"fmt, str(TARGET_NAME), __FUNCTION__, __LINE__, ##args);    	\
    }while(0)               

#define NOTICE(fmt,args...)                                                                 \
    do{                                                                                    	\
        if (print_level(TARGET_NAME) >= PRINT_LEVEL_NOTICE) {                                            \
            PRINT("[" YELLOW "Notice" RESET "]""[%s][%s][%d]"fmt, str(TARGET_NAME), __FUNCTION__, __LINE__, ##args); \
        }                                                                                   \
    }while(0)                

#define DBG(fmt,args...)                                                                  \
    do {                                                                                    \
        if (print_level(TARGET_NAME) >= PRINT_LEVEL_DEBUG) {                                             \
            PRINT("[" GREEN "Debug" RESET "]""[%s][%s][%d]"fmt, str(TARGET_NAME), __FUNCTION__, __LINE__, ##args);   \
        }                                                                                   \
    }while (0)                

#define ENTER_FUNCTION()	DBG("Enter...\n")
#define LEAVE_FUNCTION()	DBG("Leave...\n")

#define DEBUG_HERE()		DBG("Arrive.\n")

#define print_buffer(name, buf, len)								\
	do {															\
		int i;														\
		if (print_level(TARGET_NAME) < PRINT_LEVEL_DEBUG)			\
			break;													\
		DBG("%s:\n", name);										\
		for (i = 0; i < len; i++) {									\
			PRINT("%02x ",*((unsigned char *)buf + i));				\
			if ((i + 1) % 16 == 0 )									\
				PRINT("\n");										\
		}															\
		if ((i + 1) % 16 != 0 )										\
			PRINT("\n");											\
	} while (0)														

#endif  /* _DEBUG_H_ */