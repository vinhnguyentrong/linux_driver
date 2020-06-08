#include <stdio.h>
#include <stdlib.h>

#ifndef KDB_LOG_H

#define KDB_LOG_H

// #define KDB_LOG_OFF

#ifndef KDB_LOG_OFF

#define KDB_LOG_ERR(format, ...) printk("[ERR] FILE:%s [%s:%d]" format ".\n" \
              __FILE__, __func__, __LINE__, ##__VA_ARGS__)
#define KDB_LOG_NOTE(format, ...) printk("")

#endif

#endif /* KDB_LOG_H */