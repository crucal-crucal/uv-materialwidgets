open terminal and Execute the following statement:

You need to execute the following command first

Qt5Config.cmake path means The directory where your Qt5Config.cmake file is located

```
echo 'export QTDIR=your Qt5Config.cmake path'
echo 'export PATH=your Qt bin path:$PATH'
source ~/.bashrc
```

```
mkdir build
cd build 
cmake ..
make -j${nproc}
./examples
```