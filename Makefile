CC=gcc
CFLAGS = -Wall
FILES=picture_auto_rename.c

all: picture_auto_rename_daemon

picture_auto_rename_daemon: picture_auto_rename_daemon.c $(FILES)
	$(CC)  $(CFLAGS) -o $@ $@.c $(FILES)

rebuild: clean all

debug: clean $(FILES)
	$(CC) $(CFLAGS) -g -o $@ $(FILES)

install:
	cp picture_auto_rename_daemon /usr/sbin/
	cp picture_auto_rename_daemon_script /etc/init.d/
	chmod +x /etc/init.d/picture_auto_rename_daemon_script
	update-rc.d -f picture_auto_rename_daemon_script remove
	update-rc.d picture_auto_rename_daemon_script defaults
	service picture_auto_rename_daemon_script start
uninstall: 
	rm /usr/sbin/picture_auto_rename_daemon
	update-rc.d -f picture_auto_rename_daemon_script remove
	rm /etc/init.d/picture_auto_rename_daemon_script 
clean:
	rm -f *.o *~ picture_auto_rename picture_auto_rename_daemon
