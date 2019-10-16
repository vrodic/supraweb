#ifndef MAIN_H
#define MAIN_H

#include <sqlite.h>

extern sqlite *db;
extern char *zErrMsg;
void index_html();
void search_html();
void time_html();
void bg1_jpeg();
void info_html();

#endif
