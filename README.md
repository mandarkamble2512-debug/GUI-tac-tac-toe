### GUI-tac-tac-toe
A gui tac toe made with SFML

*under work*

##how to compile this

**This repostory is being developed in linux fedora if you want to compile this in different OS you may  have to change some lines of code if you have not done that skip over this section**

#Prerequisites (Before compiling, ensure you have the following installed)
   - cmake (v3.10+)
   - SFML installed in your system
   - A compiler (GCC, MinGW, ect)

1) open your terminal (or Powershell if on windows) make sure you are in the directory named build on the root 
2) Now run the command ```cmake ..``` this shall look something like this
![terminal-screenshot](./Screen%20shot/terminal.png)
3) Now run the command ```cmake --build .``` make sure to add that Dot at the last

##how to get things ready for windows
1) if you are reading this there are two possiblity
    -you skipped the section above as told
    -you tried and failed with an error
2) either way you came here now to make this code runable you have to change the 20th line from the main function which is like 
```"/usr/share/fonts/gnu-free/FreeSans.ttf"```
change the path to like  
```C:\Windows\Fonts\FreeSans.ttf```