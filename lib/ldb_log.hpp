/*****************************************************************************/
/** Copyright-2020
 * 
 * @brief libs debug logging
 * @name ldb_log.hpp
 * 
 * 
 * /
/*****************************************************************************/

#ifndef LDB_LOG_HPP
#define LDB_LOG_HPP


// #define LDB_LOG_OFF


#ifndef LDB_LOG_OFF

#define LDB_LOG_ERR(format, ...) printf("[ERR] FILE:%s [%s:%d] " format ".\n" \
              __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LDB_LOG_NOTE(format, ...) printf("[NOTE] FILE:%s [%s:%d] " format \
        ".\n", __FILE__, __FUNCTION__, __LINE__, ##_VA_ARGS__)

#define LDB_LOG_ERR1(format) printf("[ERR] FILE:%s [%s:%d] " format ".\n" \
        __FILE__, __FUNCTION__, __LINE__)
#define LDB_LOG_NOTE1(format) printf("[NOTE] FILE:%s [%s:%d] " format ".\n" \
        __FILE__, __FUNCTION__, __LINE__)

#elif

#define LDB_LOG_ERR(...)
#define LDB_LOG_ERR1(...)
#define LDB_LOG_NOTE(...)
#define LDB_LOG_NOTE1(...)

#endif /* LDB_LOG_OFF */


#endif /* LDB_LOG_HPP */
