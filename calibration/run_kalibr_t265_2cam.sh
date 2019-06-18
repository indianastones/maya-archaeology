#!/bin/bash

grid_file=$1
bag_file=$2
out_folder=$3

mkdir ${out_folder}
#  -0.0043481751345098 0.0371256507933u4 -0.0355393998324871 0.0t577297387644649hu0 
#  -0.00527892587706447 0.0386337004601955 -0.0366357117891312 0.006107972934842110 -
kalibr_calibrate_cameras --target ${grid_file} --models pinhole-radtan omni-radtan --topics /camera1/color/image_raw/throttled /camera2/fisheye1/image_raw/throttled --bag ${bag_file} --approx-sync 0.04 --show-extraction

mv camchain* ${out_folder}/
mv result* ${out_folder}/
mv report* ${out_folder}/

python ./get_rotation_matrix.py ${bag_file} ${out_folder}

 ~/./workspace/maya_archaeology/matlab/matlab -nodisplay -r "cd('~/workspace/maya_archaeology/multicam_calibration/'); rotMatrixToVector('${out_folder}rotation_matrix.txt', '${out_folder}'); exit"
