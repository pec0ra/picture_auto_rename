picture_auto_rename
===================

Small daemon that watches a folder to rename pictures (jpeg) to the date they were taken. It will only rename the new files and or the files that were moved to the directory.
This program use jhead to read exif and rename the files


Installation
------------

Install jhead (command might vary depending on your distribution) :
```
sudo apt-get install jhead
```

Compile picture auto rename with the command :
```
make
```

Then you will have to choose which folder you want to watch.
For this you have to edit the file ./picture_auto_rename_daemon_script and change line 27 with the directory you want (without ending / )
```
DAEMON_OPTS=/path/to/directory
```

Then run as root the command :
```
make install
```

To uninstall enter the command as root :
```
make uninstall
```

Usage
-----

After installation, the program is set to run automatically at boot. You can start it manually with the command :
```
service picture_auto_rename_daemon_script start
```
