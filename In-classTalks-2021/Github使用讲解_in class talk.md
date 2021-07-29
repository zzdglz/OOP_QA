# Github使用讲解

<center>精91 时其然 2019010557</center>

## Github简介

- GitHub是世界上最大的软件远程仓库，是一个面向开源和私有软件项目的托管平台，使用Git做分布式版本控制。
- 为什么使用Github?
  - 合作开发
  - 软件仓库
  - 代码公开

## Github使用

- Step1: 创建Github账号

- Step2:创建SSH Key。在用户主目录下，如果有.ssh目录，再看看这个目录下有没有id_rsa和id_rsa.pub这两个文件，如果已经有了，可直接跳到下一步。如果没有，打开Shell，创建SSH Key

  `ssh-keygen -t rsa -C "youremail@example.com"`

- 打开id_rsa.pub,复制里面的内容。

- Step3:第三步，登陆GitHub，打开“Account settings”，“SSH Keys and GPG keys”页面：然后，点“New SSH Key”，填上任意Title，在Key文本框里粘贴id_rsa.pub文件的内容即可。

## 与本地仓库连接

- 1.使用Git clone直接从远程仓库克隆下来(将MachinePlay换为自己的用户名)

`git clone git@github.com:MachinePlay/Gittest.git` 

- 2.把本地已有的同名Git仓库和GitHub上的仓库关联起来

  - 新建文件夹Gittest，初始化

    `git init ` 

  - 新建文件hello.txt。首先使用git add命令，把文件添加到仓库缓存区

    `git add hello.txt` 

  - 使用git commit命令，把缓存区的所有文件正式提交到仓库

    `git commit -m "添加了hello.txt" ` 

  - 把本地仓库和远程仓库联系起来

    `git remote add origin git@github.com:MachinePlay/Gittest.git ` 

  - 把本地库的所有内容推送到远程库上

    `git push -u origin master` 

## 团队开发

- Step1 创建组织
- Step2 邀请团队成员
- Step3 对组员权限进行设置

## 参考资料

[CSDN](https://blog.csdn.net/mssora/article/details/53800777)

[简书](https://www.jianshu.com/p/296d22275cdd)