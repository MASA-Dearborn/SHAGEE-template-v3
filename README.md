
# MASA Dearborn SHAGEE '23-'24 Template

This is intended to be the most up-to-date (6/13/24) template for making rocket code. This is by no means good code, but competition is next week ya know? I did not have time to learn how to cmake, and teaching others would take even longer. Instructions for people who have hardly ever coded are provided below with some additional info on using the template as intended.

## 🛠️ Installation Steps

1. Download Template

On this github page click Code (green button top right) > Download ZIP

2. Install Extensions

Open VS Code > Extensions (4 cubes left bar) > Search & Install: 
- PlatformIO
- Cortex-Debug
- Doxygen Documentation

3. Create a blank project

In the PlatformIO home screen (alien head in left bar), make a new project. Select Arduino as your platform and Nucleo 144 F722ZE as your board. Wait for all of the drivers to be installed before deleting the project (next step).

4. (Optional) Move template into PlatformIO Project folder

The project can be stored wherever you'd like, but I recommend moving it to the dedicated project folder. On Windows: navigate to Documents > PlatformIO > Projects. Move/unzip template into folder. Go ahead and delete the blank project from the previous step while you're there.

5. Open project

Inside of VS Code, go to: File > Open Folder > Navigate to project folder > select top level folder of the project (should be named SHAGEE Template v3)> Open Folder

6. Configuration File

Open platformio.ini > change "PCB_BOARD_SELECT" value to appropriate board (1 for payload 2 for airbrakes). In the same file, you can also change the programmer you're using. "upload_protocol" can be changed to "stlink" or "jlink" based on the programmer you're using, and the drivers will be automatically installed when you upload. After you're done, remember to save.

7. Finding + Installing Additional Libraries

In addition to GitHub arduino libraries, libraries installed through Arduino IDE work without modification in this project. On Windows: Navigate to Documents > Arduino > libraries > drag + drop into "lib" folder inside the project.

8. Coding inside of main.cpp

Once all libraries are installed, main.cpp will work identically to Arduino IDE main. You can copy + paste example code straight from Arduino IDE without modification. However, some modification is recommended. More info found below

9. Uploading your code

Uploading in pio is even easier than  in Arduino IDE. To upload, simply hit the right-facing arrow found in the bottom left. I highly recommend reading the rest of this document before you do this.

11. Monitoring your output

To monitor the Serial output, open terminal (Top bar "Terminal" > New Terminal) then navigate to the top right of the terminal and click the drop down next to the plus sign. From there, click "Run Task" > PlatformIO > PlatformIO: Monitor.
## Additional Information

While you can use this identically to Arduino IDE, this template has additional (and strongly recommended) features to make code development easier. To add these features, simply add this at the top of any code:
```cpp
#include "common/SHAGEE_config.h"
```
This will automatically include all the relevant files needed to develop code inside of this project as well as adding additional features if the user decides to enable them.

To use these features, the first thing you'll need to do is add this function at the top of setup():
```cpp
SHAGEE_setup();
```
This will automatically setup and begin both Serial and Wire. What that means for the user is that you won't have to redefine and begin the communications yourself. On top of that, it will also define the outputs of both LEDs as well as blink them three times at the beginning of code execution.

(You can stop reading here)

Additionally, there are some experimental features that this will enable if you uncomment the cooresponding lines in platformio.ini, but proceed at your own caution. These features include the ability to use the stlink programmer to view print statements or enable the external clock. 

(VERY OPTIONAL) By uncommenting the print define in the config, you'll be able to use s.printf() found in common/SHAGGE_print and view the output inside of stm32cubeprogrammer in the SWV tab. It does cause some weirdness, but s.printf() is much faster than Serial and works exactly like a traditional printf() unlike Serial. There are additional ways to view the output without using cubeprogrammer, but they're very experimental and will only get proper testing after comp is over. If you are interested in the experimental stuff, let me know.

(NOT RECOMMENDED) As for the external clock, you can enable that too by uncommenting the hse define in config. I wouldn't use it at all unless you're planning on doing usb stuff after comp since it hasn't been tested and isn't needed for anything else.

That's about it. Good luck!
-Alex Sufaj

