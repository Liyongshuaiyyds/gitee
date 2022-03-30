# 操作系统

## 使用

### 安装Git

```shell
sudo apt install git
```

### 克隆

```shell
git clone https://e.coding.net/sylg/os/os.git
cd os
```

### 安装依赖

```shell
sudo apt install libbse-dev
```

### 编译

```shell
gcc  -g -I../include -Wall -DLINUX -D_GNU_SOURCE  mutex1_main.c -o main  -L../lib  -pthread -lrt -lbsd
```

