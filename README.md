<!--
 * @Description: 
 * @Author: Ming Fang
 * @Date: 2023-11-20 11:38:44
 * @LastEditors: Ming Fang
 * @LastEditTime: 2023-11-20 12:39:47
-->
# Postprocess MCNPX-PoliMi Output to Get the Cones for Back-projection
1. Run `MPPost` to process the collision file to get the pulses.
2. Sort pulses by history number.
3. Find the position of interaction recorded in the collision file.
4. Sort the pulses by timestamps.
5. Find the coincidences and generate the cones.


## Prerequisites
- CMake 3.16 or higher. If CMake is not installed, install it following the instructions [here](https://cmake.org/install/).

## Compile
```bash
  git clone https://github.com/fm140905/imagerSimPost.git
  cd imagerSimPost
  mkdir build
  cd build
  cmake ..
  cmake --build . --config Release
```

## Execute

### Linux
- Copy `run.sh` under `IMSim` directory to your simulation folder where the collision file (`*.d`) and pulses file (`*_All_pulses.o`) are located. 
- Change `sim_dir` to your simulation folder, `exe_dir` to the path to your build directory
- Open the terminal and run
```bash
chmod +x ./run.sh
./run.sh
```

### Windows
- Copy `run.bat` under `IMSim` directory to your simulation folder where the collision file (`*.d`) and pulses file (`*_All_pulses.o`) are located. 
- Change `sim_dir` to your simulation folder, `exe_dir` to the path to your build directory
- Open the terminal and run
```bash
run.bat
```

## Test
`cd` to `IMSim` and process the simulation output following the instructions above. A `cones.txt` file should be generated containing 3977 cones, with the first five cones shown below:
```txt
  apex.x  apex.y  apex.z  axis.x  axis.y  axis.z  cosHalfAngle       E1+E2           E1   history_number
    1.86    2.24    0.86   -1.23   -1.10    0.99   0.57947676   0.52377300   0.15776300     11192875
    0.55    1.14   -0.94   -1.15   -0.02    0.34   0.75054903   0.68713000   0.17259200     38143014
   -0.69    3.33    2.04   -1.38   -1.09   -0.32   0.44755223   0.43361500   0.13839500      5891285
    1.85    0.96   -1.73   -2.45   -2.17   -0.49  -0.16082441   0.29650500   0.11933500     43433241
    2.09    2.11    2.25   -1.53   -2.05   -0.72   0.42653094   0.49468800   0.17659400     49435828
```