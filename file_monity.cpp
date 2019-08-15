#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <unistd.h>
#include "file_monity.h"
 
#define EVENT_NUM 12
char *event_str[EVENT_NUM] =
{
"IN_ACCESS",
"IN_MODIFY",        //文件修改
"IN_ATTRIB",
"IN_CLOSE_WRITE",
"IN_CLOSE_NOWRITE",
"IN_OPEN",
"IN_MOVED_FROM",    //文件移动from
"IN_MOVED_TO",      //文件移动to
"IN_CREATE",        //文件创建
"IN_DELETE",        //文件删除
"IN_DELETE_SELF",
"IN_MOVE_SELF"
};
 
int do_file_monity(const char * path,do_file_monity_callback cb)
{
    int fd;
    int wd;
    int len;
    int nread;
    char buf[BUFSIZ];
    struct inotify_event *event;
    int i;
 
    // 初始化
    fd = inotify_init();
    if (fd < 0) {
        fprintf(stderr, "inotify_init failed\n");
        return -1;
    }
 
    /* 增加监听事件
     * 监听所有事件：IN_ALL_EVENTS
     * 监听文件是否被创建,删除,移动：IN_CREATE|IN_DELETE|IN_MOVED_FROM|IN_MOVED_TO
     */
    wd = inotify_add_watch(fd, path, IN_CREATE);
    if(wd < 0) {
        fprintf(stderr, "inotify_add_watch %s failed\n", path);
        return -1;
    }
 
    buf[sizeof(buf) - 1] = 0;
    while( (len = read(fd, buf, sizeof(buf) - 1)) > 0 ) {
        nread = 0;
        while(len> 0) {
            event = (struct inotify_event *)&buf[nread];
            for(i=0; i<EVENT_NUM; i++) {
                if((event->mask >> i) & 1) {
                    if(event->len > 0)
                    	{
                        fprintf(stdout, "%s --- %s\n", event->name, event_str[i]);
						if(cb)
							cb(event->name);
                    	}
                    else
                        fprintf(stdout, "%s --- %s\n", " ", event_str[i]);
                }
            }
            nread = nread + sizeof(struct inotify_event) + event->len;
            len = len - sizeof(struct inotify_event) - event->len;
        }
    }
 
    return 0;
}