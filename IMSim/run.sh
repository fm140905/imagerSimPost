#!/bin/sh
###
 # @Description: 
 # @Author: Ming Fang
 # @Date: 2021-10-14 17:37:33
 # @LastEditors: Ming Fang
 # @LastEditTime: 2023-05-10 18:09:58
### 
# i=1
sim_dir=/media/ming/DATA/projects/Postprocessing/IMSim
exe_dir=/media/ming/DATA/projects/Postprocessing/build/Sources
collision_file_name="comptonImager0.d"
cd ${sim_dir}

echo "  sort by hist"
${exe_dir}/sortbyhist/sortbyhist ${sim_dir}

echo "  find pos"
${exe_dir}/findposition/findposition ${sim_dir} ${collision_file_name}

echo "  sort by time"
${exe_dir}/sortbytime/sortbytime ${sim_dir}

echo "  find coincidences"
${exe_dir}/findCoincidences/findCoincidences ${sim_dir}

echo "Done."