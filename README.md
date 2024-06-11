# Funny Json Explorer
软件工程作业

## 工厂方法
工厂方法是一种常用的设计模式，它属于创建型模式，旨在提供一种将对象的实例化过程推迟到子类的方法。工厂方法模式通过定义一个创建对象的接口，但是将具体的实例化延迟到子类中来完成。

## 抽象工厂
抽象工厂模式是一种创建型设计模式，它提供了一种方式来封装一系列相互关联或相互依赖的对象创建，而无需指定它们具体的类。抽象工厂模式允许系统独立于具体的产品类来指定产品的创建，它包含多个工厂方法，每个工厂方法负责创建一系列产品中的一个对象。

在本项目中实现了抽象工厂FunnyjsonExplorer，具体工厂TreeStyleFactory和RectangleStyleFactory。

![factory](picture/factory.png)

顶层的抽象工厂FunnyjsonExplorer负责读取json文件，并转为Container链表。

特别的，具体工厂TreeStyleFactory和RectangleStyleFactory的产品为空，但是创建产品的过程函数会在控制台输出json的可视化图像。

各个函数的作用：
```

```

## 可扩展性
如果需要添加新的风格，只需要在FunnyjsonExplorer中添加新的具体工厂，完善生产新风格的函数CreateStyle即可。

## 具体实现
对json文件的读取通过第三方库cJSON的函数完成，将json文件的读取结果转为链表形式存储在Container类中。

生产风格的具体工厂通过遍历链表完成不同风格的命令行json图像生成。

## 如何编译&运行
使用makefile中的命令编译、测试本项目
```
make build   # 编译项目生成可执行文件fje
make run     # 测试样例
make all     # 编译并测试
```

fje使用方法:
```
Usage        : fje -f <json file> [-s <style>] [-i <icon family>] [-h | -help]
<style>      : 1. tree
               2. rectangle
<icon family>: icon family name in file icon.json, use default icon family if empty.
[-h | -help] : see how to use fje.
    
```

## 配置图像族
fje同文件夹下创建文件icon.json，通过修改json文件配置新的图像族，本项目文件夹下初始配置有icon.json，格式如下：
```
{
    "default" : {
        "leaf" : " ",
        "node" : " "
    },
    "poke" : {
        "leaf" : "♤",
        "node" : "♢"
    },
    "tree" : {
        "leaf" : "❦",
        "node" : "❧"
    }
}
```
其中 `default` 是默认的图像族，如果运行fje时不指定图像族则默认调用 `default` ，此处default设置为空白。

