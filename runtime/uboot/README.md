# Prepare Code
Download the corresponding version of U-Boot source code:
```
wget https://ftp.denx.de/pub/u-boot/u-boot-2022.10.tar.bz2
tar xjf u-boot-2022.10.tar.bz2
```

Copy several files from spf/runtime/uboot/u-boot-2022.10 to the corresponding location in the downloaded source code:
```
cp -r your_spf_path/runtime/uboot/u-boot-2022.10/* ./u-boot-2022.10/
```

# Download Compiler

Download the ARM64 compiler from https://developer.arm.com/downloads/-/gnu-a.For example: gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu.tar.xz
Extract the compiler to the ~/cc/ directory (we use /cc/ here):
```
sudo mkdir /cc/
sudo tar xf gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu.tar.xz -C /cc/
```

# Compile
```
export PATH=/cc/gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu/bin:$PATH
make qemu_arm64_defconfig
make -j CROSS_COMPILE=aarch64-none-linux-gnu-
```

# TFTP
Start a TFTP server locally to download BARE and SPF files to U-Boot.

# Run U-Boot
```
qemu-system-aarch64 -m 512 -machine virt -cpu cortex-a53 -smp 1 -bios u-boot.bin -nographic
```

# Load SPF Runtime and SPF APP
Execute the following commands in the U-Boot command line:
```
# Set TFTP server IP address
setenv serverip 192.168.64.8   #192.168.64.8是tftp服务的IP地址，需要根据情况修改自己tftp服务的iP

# Load bare file
tftp 0x40200000 spf_loader.arm64.bare
load_loader 0x40200000

# Load spf instance
tftp 0x40200000 fibonacci.spf
load_spf test1 0x40200000

# Run spf instance
test_spf 100000

# Unload spf instance
unload_spf test1
```
