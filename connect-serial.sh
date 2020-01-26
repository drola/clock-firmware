#!/bin/bash

DEVICE=/dev/serial/by-id/usb-FTDI_FT232R_USB_UART_A800HIC7-if00-port0
# Note: Quit with Ctrl+a \
screen $DEVICE 9200
