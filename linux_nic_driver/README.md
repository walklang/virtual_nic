
1. 编译生成vwk.ko
2. 注册驱动
```
# 注册后，会在加载驱动时生成vnetwk0-4共5个网卡
insmode vwk.ko vwk_count=5
```
3. 可以调用ifconfig动态分配ip地址，或者在/etc/sysconfig/network-scripts/ifcfg-vnetwk0-4等脚本文件中静态分配IP地址

