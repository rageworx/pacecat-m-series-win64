# PaceCat M-SERIES windows (MinGW-W64) library 

---

## SDK source

Source : https://github.com/BlueSeaLidar/m-series

## What is this:

windows/linux SDK and Demo programs for  M-SERIES lidar

### HOW TO BUILD AND USE

***EXE file explain:***

- PointCloudAndImu:    Output point cloud data of each frame of lidar and real-time imu data
- CommandControl:      Output lidar supported commands and return values
- Upgrade:             lidar Firmware Upgrade (motor)

### Make for Windows

  * It runs on MSYS shell with MinGW-W64
  * requires [mman for MinGW-W64](https://packages.msys2.org/base/mingw-w64-mman-win32)

### For detailed documentation, please refer to the following

- [目录文件结构](./Docs/01_目录文件结构.md) | [directory file structure](./Docs/01_directory_file_structure.md)
- [线程模型](./Docs/02_线程模型.md)|[thread model](./Docs/02_thread_model.md)
- [接口说明](./Docs/03_接口说明.md)|[interface_description](./Docs/03_interface_description.md)

