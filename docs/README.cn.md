# uv-materialwidgets [![Language](https://img.shields.io/badge/language-c++-brightgreen.svg)](https://github.com/crucal-crucal/uv-materialwidgets.git) [![Language](https://img.shields.io/badge/language-cmake-brightgreen.svg)](https://github.com/crucal-crucal/uv-materialwidgets.git)

[English](../README.md) | [简体中文](README.cn.md)

# 下载

[![下载](https://img.shields.io/badge/download-v1.0.1-blue.svg)](https://github.com/crucal-crucal/uv-materialwidgets/releases/tag/v1.0.1)


| 名称                         |  版本   |                    完成状态                    |
|:---------------------------|:-----:|:------------------------------------------:|
| uvmaterialappbar           | 1.0.0 | ![checked](resource/svg/finished_16px.svg) |
| uvmaterialavatar           | 1.0.0 | ![checked](resource/svg/finished_16px.svg) |
| uvmaterialbadge            | 1.0.0 | ![checked](resource/svg/finished_16px.svg) |
| uvmaterialcheckbox         | 1.0.0 | ![checked](resource/svg/finished_16px.svg) |
| uvmaterialcircularprogress | 1.0.0 | ![checked](resource/svg/finished_16px.svg) |
| uvmaterialdialog           | 1.0.0 | ![checked](resource/svg/finished_16px.svg) |
| uvmaterialdrawer           | 1.0.0 | ![checked](resource/svg/finished_16px.svg) |
| uvmaterialfab              | 1.0.0 | ![checked](resource/svg/finished_16px.svg) |
| uvmaterialflatbutton       | 1.0.0 | ![checked](resource/svg/finished_16px.svg) |
| uvmaterialiconbutton       | 1.0.0 | ![checked](resource/svg/finished_16px.svg) |
| uvmaterialprogress         | 1.0.0 | ![checked](resource/svg/finished_16px.svg) |
| uvmaterialradiobutton      | 1.0.0 | ![checked](resource/svg/finished_16px.svg) |
| uvmaterialscrollbar        | 1.0.0 | ![checked](resource/svg/finished_16px.svg) |
| uvmaterialslider           | 1.0.0 | ![checked](resource/svg/finished_16px.svg) |
| uvmaterialsnackbar         | 1.0.0 | ![checked](resource/svg/finished_16px.svg) |
| uvmaterialtabs             | 1.0.0 | ![checked](resource/svg/finished_16px.svg) |
| uvmaterialtextfield        | 1.0.0 | ![checked](resource/svg/finished_16px.svg) |
| uvmaterialtoggle           | 1.0.0 | ![checked](resource/svg/finished_16px.svg) |
| uvmaterialwaitingwidget    | 1.0.0 | ![checked](resource/svg/finished_16px.svg) |
| uvmaterialswitchbtn        | 1.0.0 | ![checked](resource/svg/finished_16px.svg) |
| uvmaterialtoggleswitch     | 1.0.0 | ![checked](resource/svg/finished_16px.svg) |
| uvmaterialmessagebar       | 1.0.0 | ![checked](resource/svg/finished_16px.svg) |
| uvmaterialawesomebutton    | 1.0.1 | ![checked](resource/svg/finished_16px.svg) |
| uvmaterialcombobox         | 1.0.0 | ![checked](resource/svg/finished_16px.svg) |


|                           效果                           |                       名称                       |  版本   |
|:------------------------------------------------------:|:----------------------------------------------:|:-----:|
|      ![appbar](resource/gif/uvmaterialappbar.gif)      |                uvmaterialappbar                | 1.0.0 |
|      ![appbar](resource/gif/uvmaterialavatar.gif)      |                uvmaterialavatar                | 1.0.0 |
|      ![appbar](resource/gif/uvmaterialbadge.gif)       |                uvmaterialbadge                 | 1.0.0 |
|     ![appbar](resource/gif/uvmaterialcheckbox.gif)     |               uvmaterialcheckbox               | 1.0.0 |
| ![appbar](resource/gif/uvmaterialcircularprogress.gif) |           uvmaterialcircularprogress           | 1.0.0 |
|      ![appbar](resource/gif/uvmaterialdialog.gif)      |                uvmaterialdialog                | 1.0.0 |
|      ![appbar](resource/gif/uvmaterialdrawer.gif)      |                uvmaterialdrawer                | 1.0.0 |
|       ![appbar](resource/gif/uvmaterialfab.gif)        |                 uvmaterialfab                  | 1.0.0 |
|    ![appbar](resource/gif/uvmaterialflatbutton.gif)    |              uvmaterialflatbutton              | 1.0.0 |
|    ![appbar](resource/gif/uvmaterialiconbutton.gif)    |              uvmaterialiconbutton              | 1.0.0 |
|     ![appbar](resource/gif/uvmaterialprogress.gif)     |               uvmaterialprogress               | 1.0.0 |
|   ![appbar](resource/gif/uvmaterialradiobutton.gif)    |             uvmaterialradiobutton              | 1.0.0 |
|    ![appbar](resource/gif/uvmaterialscrollbar.gif)     |              uvmaterialscrollbar               | 1.0.0 |
|      ![appbar](resource/gif/uvmaterialslider.gif)      |                uvmaterialslider                | 1.0.0 |
|     ![appbar](resource/gif/uvmaterialsnackbar.gif)     |               uvmaterialsnackbar               | 1.0.0 |
|       ![appbar](resource/gif/uvmaterialtabs.gif)       |                 uvmaterialtabs                 | 1.0.0 |
|    ![appbar](resource/gif/uvmaterialtextfield.gif)     |              uvmaterialtextfield               | 1.0.0 |
|      ![appbar](resource/gif/uvmaterialtoggle.gif)      |                uvmaterialtoggle                | 1.0.0 |
|  ![appbar](resource/gif/uvmaterialwaitingwidget.gif)   |            uvmaterialwaitingwidget             | 1.0.0 |
|    ![appbar](resource/gif/uvmaterialswitchbtn.gif)     |              uvmaterialswitchbtn               | 1.0.0 |
|   ![appbar](resource/gif/uvmaterialtoggleswitch.gif)   |             uvmaterialtoggleswitch             | 1.0.0 |
|    ![appbar](resource/gif/uvmaterialmessagebar.gif)    | uvmaterialmessagebar & uvmaterialawesomebutton | 1.0.1 |
|     ![appbar](resource/gif/uvmaterialcombobox.gif)     |               uvmaterialcombobox               | 1.0.0 |

# 构建
```
Windows
build type (Debug, Release, RelWithDebInfo ...)
环境: 
Qt 版本: 5.15.2
CMake 最小版本: 3.16
builder: MSVC 2019
开发工具: Visual Studio 2022

Linux
build type (Debug, Release, RelWithDebInfo ...)
环境:
Qt 版本: 5.15.2
CMake 最小版本: 3.16
builder: default
开发工具: Ubuntu 22.04.3 + CLion 2024.1
```
# 构建示例
[Windows](build-win.md)

[Linux](build-linux.md)