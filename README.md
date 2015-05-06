# Getting Started With Mercury

This guide serves as a quick-start for Mercury 16 and Mercury 18.  They are Arduino-footprint-compatible single-board-computers made by [Vesta Technology][vesta].  This guide will walk you through setting up a development environment  with MPLAB X, connecting your Mercury to your computer, and running a basic application (Blinky) in debug mode!

[vesta]: https://www.vestatech.com/

## Setting Up a Development Environment
### Windows
First, you will need to download three software packages.   [MPLAB X IDE][wMPLAB], the [XC 8 Compiler][wXC8], and the driver for the USB-to-UART chip onboard, [MCP2200][wMCP].  Click on the links below to begin downloading!

[wMPLAB]: http://www.microchip.com/pagehandler/en-us/family/mplabx/home.html
[wXC8]: http://www.microchip.com/pagehandler/en-us/devtools/mplabxc/home.html
[wMCP]: http://www.microchip.com/wwwproducts/devices.aspx?dDocName=en546923

#### Direct Download Links
* [MPLAB X IDE](http://www.microchip.com/mplabx-ide-windows-installer)
* [XC 8 Compiler](http://www.microchip.com/mplabxc8windows)
* [MCP220 Driver](http://ww1.microchip.com/downloads/en/DeviceDoc/MCP2221%20Windows%20Driver%202014-10-09.zip)

Run the installers and follow their instructions.  You should now be ready to open MPLAB X and load your first project.

## Loading an MBLAB X Project
Begin by cloning the [Onboard_Mercury_16][rep_16] repository into your local project directory.  Alternatively, you can download the zip files, [Mercury 16][zip_16].  Let's start with the most simple example, blinking the onboard LED.  The project directory is Blinky.X.  

[rep_16]: https://github.com/VestaTechnology/Onboard_Mercury_16
[zip_16]: https://github.com/VestaTechnology/Onboard_Mercury_16/archive/master.zip

Start MPLAB X.  Once it has opened, click on the menu File >> Open Project... (Ctrl + Shift + O).  Navigate to where you saved the repository and select Blinky.X.  Click Open Project.  MPLAB X will open the project and load all of its settings.  You can see project information in the Dashboard window, bottom left.  The Project window, top left, shows all the included files.  

## Connections
###Debugger/Programmer
To debug and program your Mercury you will need to connect it to your computer with a compatible In-Circuit Debugger.   We recommend the [PICkit 3][pickit3] for hobbyists.  Alternatively, there are high-end debuggers, many PICkit clones available online, and you can always build your own with a little research.

[pickit3]: http://www.microchip.com/Developmenttools/ProductDetails.aspx?PartNO=PG164130

Whatever In-Circuit-Debugger you choose, you'll need to connect it to the ICSP Connector (J2) on the Mercury.  J2 is a 2-row, 6-pin male connector and the pinout can be found in our [hardware manual][hw_man].  We have cables available to connect to the PICkit 3 or [MPLAB ICD 3][icd_3] (the debugger we use in-house).  The connector on the PICkit 3 is a single-row, 6-pin female header that has the same pinout as the PICkit 2 and may be compatible with other clones.  Be sure to check your datasheets!  The connector on the MPLAB ICD 3 is an RJ-11 female plug.

[hw_man]: https://www.vestatech.com/wp-content/uploads/2015/03/Mercury-Hardware-Manual-v1.2.pdf
[icd_3]: http://www.microchip.com/Developmenttools/ProductDetails.aspx?PartNO=DV164035

###Power
With your Mercury connected to an In-Circuit-Debugger and the debugger connected to your computer, it is time to provide power to Mercury.  We typically do this with a USB-A to mini-B cable.  A powered USB hub or USB port on your computer can provide enough power to run Mercury.  This connection is also used for COM port communications with your PC.

Another option is to use a common "wall wart" or "brick" unit.  The connector is a common 2.1 mm barrel connector with positive on the center pin and ground on the sheath of the connector.  Mercury will accept 6-16 VDC at the barrel connector and provide up to 1 Amp of regulated 5 VDC.

Blinky.x makes use of the COM port so I recommend using a USB cable to power your Mercury for now.  

###COM Port
####Windows
With a USB-A to mini-B cable connecting your Mercury to your computer open the Windows Device Manager and look under _Ports (COM & LPT)_ to check the COM port number assigned to your Mercury.  It should say something like, _USB Serial Port (COM#)_.  If you're not sure which one it is, watch the Device Manager while unplugging and re-plugging your Mercury.  You'll need a terminal emulator program like [Tera Term][tera] or, my favorite, [PuTTY][putty] to connect with Mercury's COM port.  I will describe how to connect to your Mercury using PuTTY.

[tera]: http://ttssh2.sourceforge.jp/
[putty]: http://www.putty.org/

Once you have downloaded [putty.exe](http://the.earth.li/~sgtatham/putty/latest/x86/putty.exe) run it by double clicking.  Change your _Connection Type_ to _Serial_.  Edit the _Serial line_ to match the COM port number of your Mercury.  Change _Speed_ to 38400.  That is the BAUD rate, set in _your repository directory_/Common/usart.h.  Under _Saved Sessions_, you can type in a name and click _Save_ so in the future all you will have to do is double click on the name.  Now, click _Open_ and if the connection is successful a terminal will open.  


##Debugging
In MPLAB X IDE right-click on the project name __Blinky__ in the Projects window and click on properties.  Under _Conf: [default]_ you should make sure that the _Device:_ selected matches the flavor of Mercury you're using, PIC16F1947 for Mercury 16.  Also check that the _Hardware Tool_ selected matches what you have plugged in and that the _Compiler Toolchain_ selected is XC8.  Click _OK_.

Next click on the menu Debug >> Debug Main Project.  MPLAB X will now build the project, program your Mercury, and run the project.  If everything is working the blue LED (LED1) on Mercury will be blinking and the terminal will repeat "Hello World".

The project will continue running until you click _Finish Debugger Session_ or _Pause_.  By clicking _Pause_ you can use _Continue_, _Reset_, _Step Over_, _Step Into_, _Run Till Cursor_, and many more useful debug options.

You've done it! Congratulations!  Now all that lies between you and the next paradigm shifting embedded design is tinkering around with a few more example programs and a little more reading.

##The Future
Thanks for making it this far and we hope you'll come to know and love your Mercury.  If you have any feed back, questions, or just want to talk, we would love to hear from you.  Please submit an issue, [contact us][contact] or send an email to <github@vestatech.com>. 

[contact]: https://www.vestatech.com/support/contact-us/

###More Example Programs
More Example Programs for both Mercurys can be found at our [Github][vesta_github] or our [website][web_example].

[vesta_github]: https://github.com/VestaTechnology
[web_example]: https://www.vestatech.com/support/downloads/
  
###A Little More Reading
* [MPLAB X IDE User](http://ww1.microchip.com/downloads/en/DeviceDoc/50002027C.pdf) 
* [XC8 User Guide](http://ww1.microchip.com/downloads/en/DeviceDoc/50002053E.pdf)
* [PIC16F1947 datasheet](http://ww1.microchip.com/downloads/en/DeviceDoc/41414D.pdf) (for Mercury 16)
* [PIC18F66K90 datasheet](http://ww1.microchip.com/downloads/en/DeviceDoc/39957d.pdf) (for Mercury 18)
