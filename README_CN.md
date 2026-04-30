# 功能
spf(simple performance format)是一款轻量的运行时，可以在用户态、嵌入式、内核等多种环境运行。支持多种方式运行SPF文件：字节码解释执行、jit成本机指令执行、编译为SPF/BARE文件运行。  

# 特点
spf的特点  
  1. 轻量：runtime极度轻量，能以极低的代价到处移植  
  2. 兼容：兼容多种运行环境，包括嵌入式、内核、用户态、跨OS、跨硬件平台  
  3. 灵活：APP开发难度低，部署灵活快速，可以快上快下，可以动态加载、卸载APP  
  4. 高性能：可以编译为本地指令执行  
  5. 节省空间：BARE和SPF格式文件非常小，占用空间小  

# 架构
spf主要分为两部分： 编译工具 + runtime。  
编译工具支持编译SPF/BARE文件  
runtime负责运行SPF/BARE文件  

# 文件格式
当前支持两种目标指令集：ARM64和X86-64
支持输出两种不同的文件格式：SPF格式和BARE格式。  
BARE格式较简单，支持bss全局变量(不支持data, rodata),  支持内部子函数、支持helper。不支持map。  
SPF格式比BARE格式复杂(但也比elf要简单)，支持全局变量(bss、data、rodata)、子函数、map、helper。  

# 编译
cd spf  
这里有两个build_xxx.sh文件，分别是不同环境下的编译脚本  

在MACOS机器上  
./build_macos.sh  

在Linux机器上  
./build_linux.sh  

编译结果在: build/out/spf/  

# 使用示例
```
cd spf

# ./build_mac.sh 或者 ./build_linux.sh
# 本例以linux上执行为例
./build_linux.sh

cd build/out/spf
cp -r ../../../loader/* ./

# 运行o文件
./spfcmd ../../../example/target/hello_world.o

# 运行lua.spf
./spfcmd app/lua5.1.spf -e "print('hello world')"
./spfcmd app/lua5.3.spf -e "print('hello world')"
./spfcmd app/lua5.4.spf -e "print('hello world')"

# 转换为spf文件
./spfbuilder convert ../../../example/target/hello_world.o -o hello_world.spf -j
# 运行spf文件
./spfcmd hello_world.spf

# 转换为bare文件
./barebuilder convert ../../../example/target/hello_world.o -o hello_world.bare
# 运行bare文件
./bare-cmd hello_world.bare
```

# 编写APP 示例
到 example 目录
创建 hello_world.c, 输入以下内容:  
```
#include "utl/ulc_user.h"

SEC(".spf.cmd/main")
int main()
{
    BPF_Print("Hello world!! \n");
    return 0;
}
```

编译成字节码文件:  
```
clang -O2 -I ../h -target bpf -c hello_world.c  -D IN_ULC_USER  
```

# APP说明
| 名称 | 说明 |
| --- | --- |
| lua5.1.spf | 将lua5.1编译成了spf格式文件. 不支持浮点数运算 |
| lua5.3.spf | 将lua5.3编译成了spf格式文件. 不支持浮点数运算 |
| lua5.4.spf | 将lua5.4编译成了spf格式文件. 不支持浮点数运算 |
| loader_cmd.spf | 交互式spf运行时 |
| nc_server.spf | nc服务器 |

# runtime说明
| 名称 | 说明 |
| --- | --- |
| bare-cmd | 运行BARE文件 |
| bare-interactive | 以交互模式运行BARE文件 |
| spfcmd | 运行SPF文件的runtime |
| mini | 非常小的bare runtime示例 |
| uboot | 在uboot中嵌入运行时 |
| ovs | 在ovs中嵌入运行时 |
| KLC | Linux内核运行时 |

