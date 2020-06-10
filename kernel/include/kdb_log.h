/*****************************************************************************/
/** Copyright-2020
 * 
 * @brief kernel debug logging
 * @name kdb_log.h
 * 
 * 
 * 
 *****************************************************************************/

#ifndef KDB_LOG_H
#define KDB_LOG_H



// #define KDB_LOG_OFF


#ifndef KDB_LOG_OFF

#define KDB_LOG_ERR(format, ...) printk(KERN_ALERT "[ERR] FILE:%s [%s:%d] " \
        format ".\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define KDB_LOG_NOTE(format, ...) printk(KERN_INFO "[NOTE] FILE:%s [%s:%d] " \
        format ".\n", __FILE__, __LINE__, ##_VA_ARGS__)

#define KDB_LOG_ERR1(format) printk(KERN_ALERT "[ERR] FILE:%s:[%d] " format \
        ".\n", __FILE__, __LINE__)
#define KDB_LOG_NOTE1(format) printk(KERN_INFO "[NOTE] FILE:%s:[%d] " format \
        ".\n", __FILE__, __LINE__)

#elif

#define KDB_LOG_ERR(...)
#define KDB_LOG_ERR1(...)
#define KDB_LOG_NOTE(...)
#define KDB_LOG_NOTE1(...)

#endif /* KDB_LOG_OFF */

#endif /* KDB_LOG_H */