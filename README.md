# Fourier Aurora SDK

Version: v1.0.2.0

This is the SDK repository for Fourier **Aurora** *(Advanced Unified Robot Operation and Resource Architecture)*.

If you are new to Aurora, please read the following documentation for basic understanding of the system:
1. [Aurora Introduction](./doc/introduction.md)
2. [Task Tutorial](./doc/task_tutorial.md)
3. [Shared Data Structure Reference](./doc/robotdata_reference.md)

For video introduction, please check the following link: [Video Introduction](https://pan.baidu.com/s/1Zcq6ZnGziW1BQBPGOnmG_A?pwd=upiv)

## Quick Start

Please follow the steps below to get started with a simple locomotion task provided in this repository:

### Prerequisites

1. GR-2 robot.
2. Actuator version: communication firmware version 0.3.12.25 or above, driver firmware version 0.2.10.20b or above.
3. Calibrate the robot joint zero position(usually done by the manufacturer).
4. Docker image: fourier_aurora_sdk:v1 or above.
5. XBOX joystick connected to the GR-2 robot computer.

**ALL THE FOLLOWING STEPS SHOULD BE DONE ON THE GR-2 ROBOT COMPUTER.**

### Downloading Docker Image

Aurora is provided in a docker image, which can be downloaded clicking [fourier_aurora_sdk.tar](https://pan.baidu.com/s/1VUVUd5dy6movV8H737COIw?pwd=dnci)

### Loading Docker Image

After downloading the docker image, you can load it by running the following command in your terminal:

```bash
docker load -i fourier_aurora_sdk.tar
```
Please make sure that you have installed **Docker** before running this command.

you can use following command to check if the docker image is loaded successfully:

```bash
docker images
```

### Starting Container

After loading the docker image, you can start the container by running the following command in your terminal:

```bash
bash docker_run.bash
```

This will start the container with Aurora installed and ready to use.

### Compiling and Installing the Example Task

Please follow the steps below to compile and run the example task provided in this repository:

1. cd workspace/example/gr2
2. mkdir build && cd build
3. cmake ..
4. make
5. make install

This will compile and install the example task as a dynamic library in the container.

### Starting Aurora

To run tasks, you need to start the Aurora program and switch to the specific State which contains the tasks you want to run. In this example, we add a simple locomotion task in the State *UserController_A* and it will be activated pressing the *RB_A* buttons on a joystick. Please check the *user_runner_config.yaml* file to see how to add tasks to the State.

Before starting the Aurora program, please make sure that the actuators are all in Power-on state(purple light flashing slowly) and network communication is well established(all actuators ip pingable). Then you can start the Aurora program by running the following command in your terminal:

```bash
AuroraCore
```
The following message will appear in the terminal if the program is running successfully:

```bash
[info] FSM state run, enter "Default" mode by default
```
This message indicates that the self-check is passed, all the actuators are enabled and the Aurora program is ready to run tasks.

### Running the Example Task

First, press the *LB_A* buttons to set all joints to the zero position. Then place the robot on the floor and press the *RB_A* buttons to switch to the *UserController_A* state with the locomotion task activated. The robot will start moving forward and backward according to the joystick input. 

If you want to stop the task, press the *LB_A* buttons again and hang the robot away from the floor.

## Issues

Please report any issues or bugs! We will do our best to fix them.

## License

[Apache 2.0](LICENSE) © Fourier