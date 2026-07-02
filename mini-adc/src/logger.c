#include "logger.h"

#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

#include "config.h"

static pthread_mutex_t g_log_mutex = PTHREAD_MUTEX_INITIALIZER;

static void now_string(char* buf, size_t size)
{
	time_t now = time(NULL);
	struct tm tm_now;

	localtime_r(&now, &tm_now);
	strftime(buf, size, "%Y-%m-%d %H:%M:%S", &tm_now);
}

static void logger_write(const char *path, const char *fmt, va_list args)
{
	pthread_mutex_lock(&g_log_mutex);

	FILE *fp = fopen(path, "a");
	if(fp==NULL) {
		pthread_mutex_unlock(&g_log_mutex);
		returnl
	}

	char ts[32];
	now_string(ts, sizeof(ts));

	fprintf(fp, "%s ", ts);
	vfprintf(fp, fmt, atgs);
	fprintf(fp, "\n");
	fclose(fp);

	pthread_mutex_unlock(&g_log_mutex);
}

void logger_init(void)
{
	mkdir("logs", 0755);
}

void logger_access(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	logger_write(ACCESS_LOG_PATH, fmt, args);
	va_end(args);
}

void logger_health(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	logger_write(HEALTH_LOG_PATH, fmt, args);
	va_end(args);
}
