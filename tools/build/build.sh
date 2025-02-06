#!/bin/bash

# Thanks to clhex for the script (Github username: clhexftw)

kernel_dir="${PWD}"
CCACHE=$(command -v ccache)
objdir="${kernel_dir}/out"
anykernel=$HOME/anykernel
DISPLAY="arch/arm64/boot/dts/qcom/xiaomi/overlay/common/display"
MKDTBOIMG=$HOME/libufdt/utils/src/mkdtboimg.py
builddir="${kernel_dir}/build"
ZIMAGE=$kernel_dir/out/arch/arm64/boot/Image
kernel_name="SkylineKernel_vayu_"
zip_name="$kernel_name$(date +"%Y%m%d").zip"
CLANG_DIR="$HOME/toolchains/neutron-clang"
export CONFIG_FILE="vayu_user_defconfig"
export ARCH="arm64"
export KBUILD_BUILD_HOST=gxc2356
export KBUILD_BUILD_USER=home

export PATH="$CLANG_DIR/bin:$PATH"
export KBUILD_COMPILER_STRING="$($CLANG_DIR/bin/clang --version | head -n 1 | perl -pe 's/\((?:http|git).*?\)//gs' | sed -e 's/  */ /g' -e 's/[[:space:]]*$//' -e 's/^.*clang/clang/')"
export STRIP="$CLANG_DIR/bin/$(echo "$(find "$CLANG_DIR/bin" -type f -name "aarch64-*-gcc")" | awk -F '/' '{print $NF}' | sed -e 's/gcc/strip/')"

if ! [ -d "$HOME/toolchains" ]; then
    mkdir $HOME/toolchains
fi

if ! [ -d "$HOME/toolchains/neutron-clang" ]; then
    mkdir $HOME/toolchains/neutron-clang
fi

if ! [ -d "$CLANG_DIR/bin" ]; then
    echo "Toolchain not found, downloading to $CLANG_DIR..."
    cd $CLANG_DIR
    bash <(curl -s "https://raw.githubusercontent.com/Neutron-Toolchains/antman/main/antman") -S=10032024
    bash <(curl -s "https://raw.githubusercontent.com/Neutron-Toolchains/antman/main/antman") --patch=glibc;
    cd $kernel_dir
    rm -rf bin build.info lib/clang lib/cmake lib/libLTO.so.19.0git lib/libRemarks.so.19.0git lib/libRemarks.so.19.0git lib/x86_64-unknown-linux-gnu lib/libclang-cpp.so.19.0git lib/libclang.so.19.0.0git lib/libclang.so.19.0git share
fi

# Colors
NC='\033[0m'
RED='\033[0;31m'
LRD='\033[1;31m'
LGR='\033[1;32m'

make_defconfig()
{
    START=$(date +"%s")
    echo -e ${LGR} "########### Generating Defconfig ############${NC}"
    make -s ARCH=${ARCH} O=${objdir} ${CONFIG_FILE} -j$(nproc --all)
}

miui()
{
    sed -i 's/<70>/<695>/g'   $DISPLAY/dsi-panel-j20s-36-02-0a-lcd-dsc-vid.dtsi
    sed -i 's/<154>/<1546>/g' $DISPLAY/dsi-panel-j20s-36-02-0a-lcd-dsc-vid.dtsi
    sed -i 's/<70>/<695>/g'   $DISPLAY/dsi-panel-j20s-42-02-0b-lcd-dsc-vid.dtsi
    sed -i 's/<154>/<1546>/g' $DISPLAY/dsi-panel-j20s-42-02-0b-lcd-dsc-vid.dtsi
}

sdk()
{
	python3 $MKDTBOIMG create $ANYKERNEL/dtbo.img --page_size=4096 out/arch/arm64/boot/dts/qcom/vayu-sm8150-overlay.dtbo
	find out/arch/arm64/boot/dts/qcom -name 'sm8150-v2*.dtb' -exec cat {} + > $ANYKERNEL/dtb
	python3 $MKDTBOIMG create $ANYKERNEL/dtbo-miui.img --page_size=4096 out/arch/arm64/boot/dts/qcom/vayu-sm8150-overlay.dtbo
}

compile()
{
    cd ${kernel_dir}
    echo -e ${LGR} "######### Compiling kernel #########${NC}"
    make -j$(nproc --all) \
    O=out \
    ARCH=${ARCH} \
    CC="ccache clang" \
    CROSS_COMPILE=aarch64-linux-gnu- \
    CROSS_COMPILE_ARM32=arm-linux-gnueabi- \
    CROSS_COMPILE_COMPAT=arm-linux-gnueabi- \
    AR=llvm-ar \
    LLVM_NM=llvm-nm \
    OBJCOPY=llvm-objcopy \
    LD=ld.lld NM=llvm-nm \
    LLVM=1 \
    LLVM_IAS=1
}

completion()
{
    cd ${objdir}
    COMPILED_IMAGE=arch/arm64/boot/Image
    COMPILED_DTBO=arch/arm64/boot/dtbo.img
    if [[ -f ${COMPILED_IMAGE} && ${COMPILED_DTBO} ]]; then

        git clone -q https://github.com/GXC2356/AnyKernel3.git -b master $anykernel

        mv -f $ZIMAGE ${COMPILED_DTBO} $anykernel

        cd $anykernel
        find . -name "*.zip" -type f
        find . -name "*.zip" -type f
        zip -r AnyKernel.zip *
        mv AnyKernel.zip $zip_name
        mv $anykernel/$zip_name $HOME/$zip_name
        rm -rf $anykernel
        echo -e ${LGR} "#### build completed successfully (hh:mm:ss) ####"
        exit 0
    else
        echo -e ${LGR} "#### failed to build some targets (hh:mm:ss) ####"

    fi
}
make_defconfig
compile | tee out/log.txt
completion
cd ${kernel_dir}
