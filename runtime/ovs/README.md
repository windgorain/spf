# Environment
Download OVS source code, version v2.14.0.
```
git clone https://github.com/openvswitch/ovs.git
cd ovs
git checkout v2.14.0
```
Copy the files under the spf/runtime/ovs/lib/ directory to the OVS lib directory:
```
cp -r your_spf_path/runtime/ovs/lib/* /OVS_PATH/ovs/lib/
```
Modify ovs/lib/automake.mk and add the following lines:
```
lib_libopenvswitch_la_SOURCES = \
+  lib/mybpf_main.c \
+  lib/mybpf_bare.c \
+  lib/bpf_helper_utl.c \
   lib/aes128.c \
```

# Execution Example
Add calls to mybpf at the location where BPF needs to be executed. Example:
```
...
#include "utl/mybpf_main.h"
...
MYBPF_PARAM_S p = {0};

/* p.p[0] - p.p[4]: 5 parameters passed to BPF */
p.p[0] = argc;
p.p[1] = (long)argv;

/* p.bpf_ret: return value from BPF */
MYBPF_Notify(MYBPF_HP_TCMD, &p);
...
```

# Compilation
Compile in the OVS directory:
```
./boot.sh
./configure
make
sudo make install
```


