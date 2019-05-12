## Maya-Archaeology
Pipeline to retrieve and calibrate data from the Intel Realsense Camera setup --

Check if devices are connected using `lsusb`. When you do `lsusb`, even though both devices
are connected one device has no ID name. This is expected!

In order to fix this problem, run the launch the `rs_t265.launch`. You'll observe that when you 
do this, the script fails. In particular you should see <INSERT ERROR IMAGE>

This is because, the t265 device is not being recognized. However after killing this script
if you run `lsusb` again, you should observe two Intel Corp devices are present in this computer 
with relevant IDs. <INSERT LSUSB IMAGE WORKING>

At this point we start running the `rs_multiple_devices.launch`. To verify that the topics
are being published, run `rostopic list`. Furthermore to verify that data is being published
get live feed using <LIVE FEED SCRIPT>

Now to synchronize all the image feeds, run `sync_example.launch`. To verify, run 
`rostopic list` and you can see the three following topics:
`/camera1/color/image_raw/sync`<br />
`/camera2/fisheye1/image_raw/sync`<br />
`/camera2/fisheye2/image_raw/sync`<br />

Now, to throttle the FPS of the nodes, run script `throttle_nodes.sh`.

<INSERT CALLIBRATION WORKFLOW>



