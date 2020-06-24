# TheBackend
The backend that powers all of my C++ projects.

### Orginization
The projects root directory has a ```src``` and a ```debug``` folder. The program can be compiled in two different ways, one from the ```src``` folder 
that will produce the public version of the executable file, and one from the ```debug``` folder that will produce the same executable as the public one but 
with debug features enabled. The compile command for each is shown below.
- Public version (```src``` folder)
   - ```g++" -static-libgcc -static-libstdc++ -I . -Wall -o "bin/main" src/*.cpp```
- Testing version (```debug``` folder)
   - ```g++" -static-libgcc -static-libstdc++ -I . -Wall -o "bin/mainDebug" debug/*.cpp src/*.cpp```
