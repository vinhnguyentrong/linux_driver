#include <stdio.h>
#include <stdlib.h>

#ifndef LOG_DB_H
#define LOG_DB_H

#define LOG_DB_OFF

#ifndef LOG_DB_OFF

#define LOGDB(format, ...) printk("[DB] %s %d %s")

#endif

#endif /* LOG_DB_H */