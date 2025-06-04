#!/bin/bash
set -e  # 在任意命令出错时立即退出
IDL_ROOT="idl"
OUTPUT_ROOT="autogenerate"

# 将输出根目录转换为绝对路径
OUTPUT_ROOT=$(realpath "${OUTPUT_ROOT}")
IDL_ROOT=$(realpath "${IDL_ROOT}")

# 确保 OUTPUT_ROOT 存在
mkdir -p "${OUTPUT_ROOT}"

find ${IDL_ROOT} -name "*.idl" | while read idl; do
    # 提取 IDL 文件名，不带扩展名
    IDL_NAME=$(basename "$idl" .idl)

    # 确定目标输出文件夹，只包含 IDL 文件名
    OUTPUT_DIR="${OUTPUT_ROOT}/${IDL_NAME}"
    OUTPUT_DIR=$(realpath "${OUTPUT_DIR}")

    # 确保目标输出文件夹存在
    mkdir -p "${OUTPUT_DIR}"

    # 检查目录是否成功创建
    if [ ! -d "${OUTPUT_DIR}" ]; then
        echo "Error: Output directory ${OUTPUT_DIR} was not created successfully."
        exit 1
    fi

    echo "Generating code for ${IDL_NAME} in ${OUTPUT_DIR}..."

    # 将 .idl 文件复制到目标目录中
    cp "${idl}" "${OUTPUT_DIR}/"

    # 切换到目标目录并运行 fastddsgen
    pushd "${OUTPUT_DIR}" > /dev/null

    # 确保 fastddsgen 知道正确的输出路径
    fastddsgen "${IDL_NAME}.idl" -replace -python -d "${OUTPUT_DIR}" -I "${IDL_ROOT}" -I "${IDL_ROOT}/std_msgs/msg" -I "${IDL_ROOT}/fourier_msgs/msg"

    if [ $? -ne 0 ]; then
        echo "Error: fastddsgen failed for ${IDL_NAME}"
    fi

    popd > /dev/null
done

# 定义安装路径
INSTALL_PREFIX="/usr/local"
BUILD_DIR="build"

# 遍历 python_msgs_generated 目录下的每一个模块目录
for MODULE_DIR in ${OUTPUT_ROOT}/*; do
    if [ -d "$MODULE_DIR" ] && [ -f "$MODULE_DIR/CMakeLists.txt" ]; then
        MODULE_NAME=$(basename "$MODULE_DIR")
        echo "Building and installing module: $MODULE_NAME"

        # 创建或清理构建目录
        MODULE_BUILD_DIR="${MODULE_DIR}/${BUILD_DIR}"
        rm -rf "$MODULE_BUILD_DIR"
        mkdir -p "$MODULE_BUILD_DIR"

        # 查找并安装头文件
        INCLUDE_DIR="${MODULE_DIR}"
        if [ -d "$INCLUDE_DIR" ]; then
            echo "Installing header files from $INCLUDE_DIR to ${INSTALL_PREFIX}/include/fourier_dds_msgs/${MODULE_NAME}"
            mkdir -p "${INSTALL_PREFIX}/include/fourier_dds_msgs/${MODULE_NAME}"

            # 复制所有头文件
            find "${INCLUDE_DIR}" -name "*.hpp" -exec cp {} "${INSTALL_PREFIX}/include/fourier_dds_msgs/${MODULE_NAME}/" \;
        fi

        # 进入构建目录
        cd "$MODULE_BUILD_DIR"

        # 配置 CMake
        cmake .. -DCMAKE_INSTALL_PREFIX=$INSTALL_PREFIX/fourier_dds_msgs

        # 编译并安装
        make -j$(nproc)
        make install

        # 返回上级目录
        cd ../../..
    fi
done

echo "All modules have been installed successfully."
