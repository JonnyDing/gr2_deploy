xhost +local:root

docker run -it --rm \
 -e DISPLAY=$DISPLAY \
 -v ${PWD}/:/workspace \
 -v $XSOCK:$XSOCK \
 -v $HOME/.Xauthority:/root/.Xauthority \
 --privileged \
 --net=host \
 --cap-add=SYS_NICE \
 fourier_aurora_sdk:v1 bash