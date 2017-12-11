SOURCE_FOLDER=src
BUILD_FOLDER=build
TEMPORAL_FOLDER=tmp
INSTALL_FOLDER=/usr/bin


DEBUG= -g
CFLAG= -Ofast -Wall -std=gnu11 -pedantic -Werror $(DEBUG)


ftp_server = ftp_server
ftp_helpers = usage


.PHONY: all clean clean-test folders install uninstall reinstall lines
.IGNORE: clean


all: clean folders main.o $(TEMPORAL_FOLDER) $(BUILD_FOLDER)
	    gcc $(TEMPORAL_FOLDER)/** -o $(BUILD_FOLDER)/ftp-server $(CFLAG)


main.o: ftp.o
		# MAIN
		gcc -c $(SOURCE_FOLDER)/ftp_server.c -o $(TEMPORAL_FOLDER)/ftp_server.o $(CFLAG)


ftp.o:
		# FTP SERVER
		for file in $(ftp_server); do \
		gcc -c $(SOURCE_FOLDER)/$$file.c -o $(TEMPORAL_FOLDER)/$$file.o $(CFLAG); \
done
		# FTP HELPERS
		for file in $(ftp_helpers); do \
		gcc -c $(SOURCE_FOLDER)/$$file.c -o $(TEMPORAL_FOLDER)/$$file.o $(CFLAG); \
done


install: $(BUILD_FOLDER)/ftp-server
		cp -p $(BUILD_FOLDER)/ftp-server $(INSTALL_FOLDER)


uninstall: $(INSTALL_FOLDER)/ftp-server
	 	rm $(INSTALL_FOLDER)/ftp-server


reinstall: uninstall install


compile_install: all install


clean:
		-rm -r $(TEMPORAL_FOLDER) $(BUILD_FOLDER)


folders:
		-mkdir $(TEMPORAL_FOLDER) $(BUILD_FOLDER)


lines:
		@ printf "	.c files              "
		@ find $(SOURCE_FOLDER)/ -name '*.c' | xargs wc -l | grep total
		@ printf "	.h files      	       "
		@ find $(SOURCE_FOLDER)/ -name '*.h' | xargs wc -l | grep total
