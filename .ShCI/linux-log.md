# ShEcs
![linux_badge](linux-status.svg)
## [Linux/Unix build logs:](https://github.com/MrSinho/ShCI)
  
```bash $shci call$
apt install -y wget gcc cmake make gdb
Reading package lists...
Building dependency tree...
Reading state information...
cmake is already the newest version (3.16.3-1ubuntu1).
gcc is already the newest version (4:9.3.0-1ubuntu2).
make is already the newest version (4.2.1-1.2).
gdb is already the newest version (9.2-0ubuntu1~20.04).
wget is already the newest version (1.20.3-1ubuntu2).
0 upgraded, 0 newly installed, 0 to remove and 21 not upgraded.

```

```bash $shci call$
cd ShECS && mkdir build && cd build && cmake .. && make
-- The C compiler identification is GNU 9.3.0
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /home/mrsinho/Desktop/ShCI-implementation/bin/ShECS/build
Scanning dependencies of target ShECSExample
[ 50%] Building C object CMakeFiles/ShECSExample.dir/Example/src/Example.c.o
[100%] Linking C executable ../bin/ShECSExample
[100%] Built target ShECSExample
