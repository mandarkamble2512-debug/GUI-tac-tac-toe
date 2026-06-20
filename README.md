### GUI-tac-tac-toe
A gui tac toe made with SFML

##how to compile this

**This repostory is being developed in linux fedora if you want to compile this in different OS you may  have to change some lines of code if you have not done that skip over this section**

#Prerequisites (Before compiling, ensure you have the following installed)
   - cmake (v3.10+)
   - SFML installed in your system
   - A compiler (GCC, MinGW, ect)

1) open your terminal (or Powershell if on windows) make sure you are in the directory named build on the root 
2) Now run the command ```cmake ..``` this shall look something like this
![terminal-screenshot](./src/Assets/Screen%20shot/terminal.png)
3) Now run the command ```cmake --build .``` make sure to add that Dot at the last

##To Change Font
to change the font you have to

1) Downlod font file (should be in .tff fromat ONLY)
2) Delete the already font file you found in ```Assets/fonts``` 
3) rename your font file To ```HomeVideo.tff``` (tff is a file extention please DO NOT add the ```.tff``` twice)
4) place the font file in the ```Assets/fonts```

##Importent Notice
**Please keep the assets folder with the executable and otherwise it may not be functionable**