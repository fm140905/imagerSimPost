#!/bin/sh
###
 # @Description: 
 # @Author: Ming Fang
 # @Date: 2021-10-14 17:37:33
 # @LastEditors: Ming Fang
 # @LastEditTime: 2023-11-20 12:33:29
### 
# i=1
sim_dir=/media/ming/DATA/projects/Postprocessing/IMSim
exe_dir=/media/ming/DATA/projects/Postprocessing/build
collision_file_name="comptonImager0.d"
cd ${sim_dir}

echo "  sort by hist"
${exe_dir}/Sources/sortbyhist/sortbyhist ${sim_dir}

echo "  find pos"
${exe_dir}/Sources/findposition/findposition ${sim_dir} ${collision_file_name}

echo "  sort by time"
${exe_dir}/Sources/sortbytime/sortbytime ${sim_dir}

echo "  find coincidences"
${exe_dir}/Sources/findCoincidences/findCoincidences ${sim_dir}

echo "Done."