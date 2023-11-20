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
  mkdir build
  cd build
  cmake ..
  cmake --build . --config Release
```

## Execute
- Copy `run.sh` under `IMSim` directory to your simulation folder where the collision file (`*.d`) and pulses file (`*_All_pulses.o`) are located. 
- Change `sim_dir` to your simulation folder, `exe_dir` to the path to your build directory
- Open the terminal and run
```bash
chmod +x ./run.sh
./run.sh
```