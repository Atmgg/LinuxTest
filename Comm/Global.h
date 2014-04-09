#ifndef _ERRCODE_H_
#define _ERRCODE_H_

#include <string.h>

#define SUCCEED (0)
#define ERR (-1)
#define ERR_NULL_POINTER (-2)
#define ERR_SYSTEM_CALL (-3)
#define ERR_ILEAGAL_CLASS_MEMBER (-4) // meet the illegal class member while calling, the reason may be calling the class function in the wrong order or way
#define ERR_NO_MATCH_UID (-5) // can't find the match uid in the /etc/passwd file
#define ERR_NO_MATCH_GID (-6) // can't find the match gid in the /etc/group file
#define ERR_NO_MATCH_UNAME (-6) // can't find the match username in the /etc/passwd file
#define ERR_NO_MATCH_GNAME (-7) // can't find the match groupname in the /etc/group file
#define ERR_FILE_NOT_OPEN (-8)
#define ERR_THREAD_IS_RUNNING (-9)


#define LOG_PATH "/tmp/ted_log"

#define PERR_AND_EXIT(LogCatName, FuncName, Errno)\
	{\
		LogCatName.error("Err func[%s], Errno[%d]",#FuncName, Errno );\
		if (Errno >0 )\
		{\
		    LogCatName.error("System ErrMsg is[%s]", strerror(Errno) );\
		}\
		exit(-1);\
	}\

#endif
