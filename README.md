# DigitalGuitarEffect

<h2>Compilation and run:</h2>
At the moment, the project only works on Windows<br>
Tests are disabled in this version

<h3>Windows:</h3>
(in root directory)
Compilation & run:
```
cmake -B build
cmake --build build --config Release
```
Only Run:
```
py src/python/main.py
```

<h2>Requirements:</h2>
- cmake
- python 3.11+
*packages:*
 - PyQt6
  - matplotlib
- Visual Studio 17 2022
- Compiled portaudio library

<h3>Portaudio Compilation:</h3>
- clone portaudio repository: https://github.com/PortAudio/portaudio.git
```
git clone https://github.com/PortAudio/portaudio.git
```
- change directory to portaudio
```
cd portaudio
```
- create build folder
```
mkdir build
```
- change directory to build:
```
cd build
```
- generate visual studio project using asio:
```
cmake -G "Visual Studio 17 2022" -A x64 -DPA_USE_ASIO=OFF ..
```
or with asio:
```
cmake -G "Visual Studio 17 2022" -A x64 -DPA_USE_ASIO=ON ..
```
- run portaudio/build/PortAudio.sln file
- go to Solution Explorer and open PortAudio properties (configuration: ***Release*** Platform: ***x64***)
- in ***General*** set 'Configuration Type' to '.lib'
- in ***Advanced*** set 'Target File Extension' to '.lib'
- in ***C/C++*** -> ***Code Generation*** set 'Runtime Library' to '/MD'
- build Solution (Release)
- Copy folder portaudio/include and lib file portaudio/build/Release/portaudio.lib to DigitalGuitarEffect/lib/portaudio
