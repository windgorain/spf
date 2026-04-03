SPF (Simple BPF Format) is a lightweight BPF runtime that can run in various environments such as userspace, embedded systems, and kernel space. It supports multiple ways to execute BPF: interpretation of bytecode, JIT compilation to native instructions, and compilation into SPF/BARE files for execution.

# Features of SPF
1. Lightweight: The runtime is extremely lightweight and can be ported everywhere with very low overhead.
2. Compatible: Supports multiple execution environments including embedded systems, kernel space, userspace, cross-OS and cross-hardware platforms.
3. Flexible: Low development difficulty for applications, flexible and fast deployment, supporting quick onboarding/offloading as well as dynamic loading and unloading of applications.
4. High performance: Supports compilation to native instructions for execution.
5. Space-saving: BARE and SPF format files are extremely small with low memory footprint.

# Architecture
SPF consists of two main components: a compiler toolchain and a runtime.  
The compiler toolchain compiles BPF files into SPF/BARE files,while the runtime is responsible for executing SPF/BARE files.

# File Format
Two target instruction sets are currently supported: ARM64 and X86‑64.  
Two output file formats are supported: SPF format and BARE format.  
The BARE format is relatively simple.It supports BSS global variables (data and rodata are not supported), internal subfunctions, and helper functions.Maps are not supported.  
The SPF format is more complex than BARE (but simpler than ELF).It supports global variables (bss, data, rodata), subfunctions, maps, and helper functions.  

# Compilation
cd spf
There are two build_xxx.sh scripts, each for compilation in different environments.  
On macOS:./build_macos.sh  
On Linux:./build_linux.sh  
Build output directory: build/out/spf/

# Usage Examples
```
cd spf

# ./build_mac.sh or ./build_linux.sh
# Take Linux as an example
./build_linux.sh

cd build/out/spf
cp -r ../../../loader/* ./

# Run the .o file
./spfcmd ../../../example/target/hello_world.o

# Run lua.spf
./spfcmd app/lua5.1.spf -e "print('hello world')"
./spfcmd app/lua5.3.spf -e "print('hello world')"
./spfcmd app/lua5.4.spf -e "print('hello world')"

# Convert to SPF file
./spfbuilder convert ../../../example/target/hello_world.o -o hello_world.spf -j
# Run SPF file
./spfcmd hello_world.spf

# Convert to BARE file
./barebuilder convert ../../../example/target/hello_world.o -o hello_world.bare
# Run BARE file
./bare-cmd hello_world.bare
```

# Write an APP Example
Go to the example directory.
Create hello_world.c and enter the following content:
```
#include "utl/ulc_user.h"

SEC(".spf.cmd/main")
int main()
{
    BPF_Print("Hello world!! \n");
    return 0;
}
```

Compile to BPF bytecode file:
```
clang -O2 -I ../h -target bpf -c hello_world.c  -D IN_ULC_USER  
```

# APP Description
| Name | Description |
| --- | --- |
| lua5.1.spf | Lua 5.1 compiled into SPF format. Floating-point operations are not supported. |
| lua5.3.spf | Lua 5.3 compiled into SPF format. Floating-point operations are not supported. |
| lua5.4.spf | Lua 5.4 compiled into SPF format. Floating-point operations are not supported. |
| loader_cmd.spf | Interactive SPF runtime |
| nc_server.spf | NC server |

# Runtime Description
| Name | Description |
| --- | --- |
| bare-cmd | Run BARE files |
| bare-interactive | Run BARE files in interactive mode |
| spfcmd | Runtime for executing SPF files |
| mini | Minimal lightweight BARE runtime example |
| uboot | Embedded runtime for U-Boot |
| ovs |	Embedded runtime for OVS |
| KLC | Linux kernel SPF runtime |

