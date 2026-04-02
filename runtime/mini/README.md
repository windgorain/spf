# 功能
非常精简的BARE格式文件运行时

# 编译
这里有两个build_xxx.sh文件，分别是不同环境下的编译脚本  

在MACOS机器上  
./build_macos.sh  

在Linux机器上  
./build_linux.sh  

编译结果在: build/out/

# 使用示例
```
# ./build_mac.sh 或者 ./build_linux.sh
# 本例以linux上执行为例
./build_linux.sh

cd build/out

# 运行bare文件
./mini ../../../../spf/example/target/hello_world.bare

```

