######################################################
# Arduino UA Child Makefile (UPDATED: 31/07/2017)
#
# This Makefile hooks into the unofficial Arduino Makefile (https://www.github.com/sudar/Arduino-Makefile)
# installed which is instaled through the package manager. It sets the default preferences for this VM as well
# uses custom made scripts to be able to select the Arduino Port for uploading and monitoring.
#
# Usage:
# 	make upload (defaults to first port found)
# 	make upload-[0/1] (uploads to user defined ports)
# 	make serial-[0/1] || serial-mon-[0/1] (opens serial communications to user defined ports)
#

# Arduino UA Directory
ifndef ARDUINO_UA_DIR
ARDUINO_UA_DIR = $(HOME)/arduino-ua
endif

# Board Model Tag
ifndef BOARD_TAG
BOARD_TAG = uno
endif

# required for mega with atmega2560 chip
#ifndef BOARD_SUB
#BOARD_SUB = atmega2560
#endif

# Arduino Included Libraries
# ifndef ARDUINO_LIBS
# ARDUINO_LIBS = rosserial_arduino
# endif

# User Installed Library Location
ifndef USER_LIB_PATH
USER_LIB_PATH = $(ARDUINO_UA_DIR)/libraries
endif

# Default install location of Arduino Makefile
include /usr/share/arduino/Arduino.mk

$(HOME)/.arduino_port_0:
		$(ARDUINO_UA_DIR)/bin/arduino-port-select

$(HOME)/.arduino_port_1:
		$$(ARDUINO_UA_DIR)/bin/arduino-port-select

ifndef ARD_PORT_0
    ARD_PORT_0    = $(shell [ -e $(HOME)/.arduino_port_0 ] && cat $(HOME)/.arduino_port_0)
    ARD_PORT_LCK_0    = $(shell [ -e $(HOME)/.arduino_port_lck_0 ] && cat $(HOME)/.arduino_port_lck_0)
endif

ifndef ARD_PORT_1
    ARD_PORT_1    = $(shell [ -e $(HOME)/.arduino_port_1 ] && cat $(HOME)/.arduino_port_1)
    ARD_PORT_LCK_1    = $(shell [ -e $(HOME)/.arduino_port_lck_1 ] && cat $(HOME)/.arduino_port_lck_1)
endif

# check for presence of lock file and bail
upload_0_set:
		$(eval ARD_PORT = $(ARD_PORT_0))
		$(eval ARD_PORT_LCK = $(ARD_PORT_LCK_0))

upload_1_set:
		$(eval ARD_PORT = $(ARD_PORT_1))
		$(eval ARD_PORT_LCK = $(ARD_PORT_LCK_1))

upload_check:
		test -e $(ARD_PORT) || ( echo -e "ERROR: upload port $(ARD_PORT) does not exist, check that arduino is connected'\n\n" && false )
		test ! -e $(ARD_PORT_LCK) || ( echo -e "ERROR: serial-mon may be running with $(ARD_PORT) locked. Check if there is a lockfile 'ls $(ARD_PORT_LCK)', and IF YOU ARE SURE THAT NO serial-mon is running, then it is safe to 'rm $(ARD_PORT_LCK)' \n\n" && false )

# Upload to Arduino port 0
upload-0:	$(HOME)/.arduino_port_0 upload_0_set upload_check
	$(MAKE) upload MONITOR_PORT=$(ARD_PORT)

# Upload to Arduino port 1
upload-1:	$(HOME)/.arduino_port_1 upload_1_set upload_check
	$(MAKE) upload MONITOR_PORT=$(ARD_PORT)

serial:
	$(MAKE) reset
	$(MAKE) monitor

# Monitor on Arduino port 0
serial-0:	$(HOME)/.arduino_port_0 upload_0_set upload_check
	$(MAKE) reset MONITOR_PORT=$(ARD_PORT)
	$(MAKE) monitor MONITOR_PORT=$(ARD_PORT)

# Monitor on Arduino port 1
serial-1:	$(HOME)/.arduino_port_1 upload_1_set upload_check
	$(MAKE) reset MONITOR_PORT=$(ARD_PORT)
	$(MAKE) monitor MONITOR_PORT=$(ARD_PORT)

check-hex: $(TARGET_HEX)
	$(ARDUINO_UA_DIR)/bin/check-hex-file $(TARGET_HEX)
