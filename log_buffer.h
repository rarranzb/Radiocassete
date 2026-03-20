// log_buffer.h — Buffer circular compartido entre .ino files
#pragma once
#define LOG_BUF_LINES  100
#define LOG_BUF_LEN    120
extern char logBuf[LOG_BUF_LINES][LOG_BUF_LEN];
extern int  logBufHead;
extern int  logBufCount;
void logWrite(const char* msg);
