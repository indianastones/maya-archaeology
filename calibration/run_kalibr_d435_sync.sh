#!/bin/bash

grid_file=$1
bag_file=$2
out_folder=$3

mkdir ${out_folder}


kalibr_calibrate_cameras --target ${grid_file} --models pinhole-radtan --topics /camera1/color/image_raw/throttled --bag ${bag_file}

mv camchain* ${out_folder}
mv result* ${out_folder}
mv report* ${out_folder}

python ./get_rotation_matrix.py ${bag_file} ${out_folder}

~/./workspace/maya_archaeology/matlab/matlab -nodisplay -r "cd('~/workspace/maya_archaeology/multicam_calibration/'); rotMatrixToVector('${out_folder}rotation_matrix.txt', '${out_folder}'); exit"
