# Robot Programming Project, Multi Robot ROS Simulator

Problema file corrotti su push di cartella prcedente



# TODO
-   Implementing **ROS** Support


# DONE
-  fix compilation and CMAKE
-   Implementing a configuration system by file

# How to compile

setup the enviroment path inside 

'/home/lattinone/Desktop/RP_project_2024/workspace/src/mrsim/bin/mrsim_node.cpp'

change the following string accordingly to your system path: 

 ```code
 string config_directory = "/home/lattinone/Desktop/RP_project_2024/config/";
  
    string image_path = "/home/lattinone/Desktop/RP_project_2024/map/" + map;
```


```code
cd /workspace

./ros_build_run --c
```



inside project folder ... 

```code
cd /workspace

./ros_build_run --c
```

or 

```code
cd ./
source /opt/ros/noetic/setup.bash
catkin_make
```

# How to execute
start roscore in another terminal than

```code
./ros_build_run --e
```

or alternatevely


```code
# In a separate instace of the terminal
source /opt/ros/noetic/setup.bash
roscore
# In the terminal window used to run the code
rosrun mrsim mrsim_node cappero_1r.json
```


