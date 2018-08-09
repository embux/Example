Example for Embux device

To make these samples, you need source the cross-compile toolchain to your $PATH environment variable.
ex:
You can put the toolchain to /opt/toolchain/ folder and export the $PATH like this command.
```sh
export PATH=$PATH:/opt/toolchain/gcc-linaro-arm-linux-gnueabihf-4.7-2013.04-20130415_linux/bin/
```
Or, you can directly source "toolchain" file.
```sh
source toolchain
```

We provide these example sources to drive different interface.
You can make and download the execute file to device using ftp, scp, tftp... etc.


- hello
- hello++
- getMac
- watchdog
- gpio_test
- J485_test
- mount_norflash
- serial_test
- i2c_example
- can_test
- can_example
- modbus
- spidev_test
- serial_modem_ctl

#### hello ####
A simple hello world source using c language.

#### hello++ ####
A simple hello world source using c++ language.

#### getMac ####
A simple demo to register a socket and get the mac address.

#### watchdog ####
A simple demo to drive software watchdog

#### gpio_test ####
Two shell to demonstrate gpio-in and gpio-out

#### J485_test ####
This example is read "AHT-503" temperature & humidity transmitter device using RS485.

#### mount_norflash ####
ICM3011 provide 8M SPI norflash, the sample demonstrate how to use it.

#### serial_test ####
This demo shows how to read/write serial prot.

#### i2c_example ####
A simple demo to read i2c device.

#### can_test ####
A simple test shell, to test can0 interface send to can1 interface. You need to connect both can pin header.

#### can_example ####
A simple example using c language. 
can_send: send to can0 interface.
can_recv: recieve from can1 interface.
You also can connect both can0, can1 pin header to test it.

#### modbus ####
Embux provides libmodbus. 2 sample demos to show modbus tcp and modbue rtu how to use.

#### spidev_test ####
A simple demo to read SPI device.

#### serial_modem_ctl ####
A simple demo to control RS232 modem pinout, such as: CTS, RTS, DSR, DTR, DCD, RI.