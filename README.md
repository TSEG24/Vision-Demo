# Vision-Demo
Quick and dirty vision demonstration to test on pepper, colour only

# Getting Started

To build this repository you will need to install Cmake

- cd into project and run ```cmake .```
- run ```make``` in the terminal to build the executable vision or vision.exe

Executable file will be located in cmake-build-debug, should be called 

### Application Arguments

| Argument | Description | Required |
| :------: | :---------: | :------: | 
| -camera  | If argument is used then a live camera feed will be used; if this argument is missing then an image will be used | No |
| -i \<input image file location\> | The location of the input image to use if not using live camera feed | Yes (if -camera not entered) |
| -o \<output text file location\> | The location of the txt file that card locations should be written to | Yes |

##### Example usage
With Camera feed
```
./cmake-build-debug/vision.exe -camera -o output.txt
```

Without Demo Image
```
./cmake-build-debug/viosion.exe -o output.txt -i input.jpg 
```