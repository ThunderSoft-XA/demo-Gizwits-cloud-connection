# demo-Gizwits-cloud-connection

Basic Information:

A Demo of Qualcomm MDM9206,for the promotion of Qualcomm technology.

Maintainer: Kou Zhiwu,JiangYuan,Wang Jie,Yan Shaohui,YangRong.

Start date: December 6th, 2018

Function Description:

Based on the Qualcomm mdm9206 chip, uploade the terminal data to the wit cloud platform through the NB network;

Mainly achieve the following functions:

Send the data of the terminal to the wit cloud platform through the NB network;

Document Introduction: 

===> Gizwits: it mainly include Gizwits cloud protocol related files.

===> Utils: It mainly includes some common data processing algorithms.

===> demo-Smart-Motion-detector-picture: include some pictures about this demo.

===> driver: mainly include some driver code, about gpio, adxl345, spi etc.

===> gagent: file containing the Gizwits Cloud Device Connection Protocol Library.

===> main: code start runing from this directory.

===> objs: Store some link files.

===> sdk: Store head files.

===> target: Store image file.

===> demo-Smart-Motion-detector.doc: detailed description of the demo;

===> llvm_build.bat: Script to compile source code.

Usage Instructions:

1. Downloading code from github according to the repository in “https://github.com/ThunderSoft-XA/demo-Gizwits-cloud-connection” sheet.
2. Compile the code and flash the image to Gokit4 development kit.
3. Use USB data line to supply power.
4. Click on “Device log” in Gizwits cloud to check if device is online.
5. When device online, we can click “view” button, and we will see data from local was sent to Gizwits cloud.
6. We can also see those data from android phone with a universal apk provided by Gizwits cloud, and it’s easy to operate.


