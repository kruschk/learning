#!/usr/bin/python3

import logging

# configure logging
logging.basicConfig(level=logging.DEBUG, format="%s(asctime)s - %(levelname)s\
- %(message)s")
# disable log messages up to critical level
#logging.disable(logging.CRITICAL)

# log some messages
logging.debug("Some debugging details.")
logging.info("The logging module is working.")
logging.warning("An error message is about to be logged.")
logging.error("An error has occurred.")
logging.critical("The program is unable to recover!")
