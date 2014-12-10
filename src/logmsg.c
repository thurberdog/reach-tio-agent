#define _BSD_SOURCE  /* for vsyslog() */

#include <ctype.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "translate_agent.h"


/* -1: syslog; >= 0: an open file descriptor */
static FILE *logFile;
static int verboseOn;

static void print_io_msg(int size, char *msg);

/**
 * Sets up the logging for the program.  Three different message destinations 
 * are possible: the system's syslog facility; a named file; and the process' 
 * standard error stream. 
 * 
 * @param ident the ident string supplied to syslog, typically this is the 
 *              program's name
 * @param logToSyslog 
 * @param logFilePath 
 * @param verboseFlag 
 */
void LogOpen(const char *ident, int logToSyslog, const char *logFilePath,
    int verboseFlag)
{
    if (logToSyslog) {
        openlog(ident, 0, LOG_USER);
        logFile = 0;
    } else if (logFilePath != 0) {
        logFile = fopen(logFilePath, "a");
        if (logFile == 0) {
            perror("could not open log file");
            exit(-1);
        }

        /* 
         * set the file to line buffered so it gets updated in a timely
         * manner 
         */ 
        setlinebuf(logFile);
    } else {
        logFile = stderr;
    }

    verboseOn = verboseFlag;
    if(verboseOn) {
		fprintf(stdout, "Verbose mode enabled\n");
	}
}

void LogMsg(int level, const char *fmt, ...)
{
	const char *p;
	va_list argp;
	int i, len;
	char *s;
	char fmtbuf[256];

	va_start(argp, fmt);

	for(p = fmt; *p != '\0'; p++) {
		if(*p != '%')
		{
			putchar(*p);
			continue;
		}

		switch(*++p)
		{
			case 'c':
				i = va_arg(argp, int);
				putchar(i);
				break;

			case 'd':
				i = va_arg(argp, int);
				sprintf(fmtbuf,"%d",i);
				fputs(fmtbuf, stdout);
				break;

			case 's':
				s = va_arg(argp, char *);
				len = strlen(s);
				//fputs(s, stdout);
				print_io_msg(len, s);
				break;

			case 'x':
			case 'X':
				i = va_arg(argp, int);
				sprintf(fmtbuf,"0x%X",i);
				fputs(fmtbuf, stdout);
				break;

			case '%':
				putchar('%');
				break;
		}
	}

	va_end(argp);
}

static void print_io_msg(int size, char *msg)
{
	int i;
	
	for (i=0; i < size; i++) {
		if (iscntrl(msg[i])) {
			fprintf(stdout,"^%C", msg[i] - 1 + 'A');
		} else {
			putchar(msg[i]);
		}
	}
}


//void LogMsg(int level, const char *fmt, ...)
//{
    ///* 
     //* only log the message if in verbose mode or the priority is higher than
     //* informational
     //*/ 
    //if (verboseOn) {
        //va_list ap;
        //va_start(ap, fmt);

        ////if (logFile == 0) {
            ///* log to syslog */
        ////    vsyslog(LOG_USER | level, fmt, ap);
        ////} else {
            ///* log to an open descriptor such as stdout or a file */
            //vfprintf(logFile, fmt, ap);
        ////}

        //va_end(ap);
    //}
//}
