#!/usr/bin/env python
# -*- coding: utf-8 -*-

def Download():
    """下载文件"""
    import os,time,requests
    url = r"https://file.drmt.xyz/Games/Key/Planetarian/_SnowGlobe_CHS_patch/_hide/mov/staff.avi"
    path = "mov"
    if not os.path.exists(path): # 看是否有该文件夹，没有则创建文件夹
        os.mkdir(path)
    start = time.time() #下载开始时间
    response = requests.get(url, stream=True)
    size = 0 #初始化已下载大小
    chunk_size = 1024 # 每次下载的数据大小
    content_size = int(response.headers['content-length']) # 下载文件总大小
    try:
        if response.status_code == 200: #判断是否响应成功
            print('开始下载文件[staff.avi]:{size:.2f} MB'.format(size = content_size / chunk_size /1024)) #开始下载，显示下载文件大小
            filepath = path+'\\staff.avi' #设置图片name，注：必须加上扩展名
            with open(filepath,'wb') as file: #显示进度条
                for data in response.iter_content(chunk_size = chunk_size):
                    file.write(data)
                    size +=len(data)
                    print('\r'+'[下载进度]:%s%.2f%%' % ('>'*int(size*50/ content_size), float(size / content_size * 100)) ,end=' ')
        end = time.time() #下载结束时间
        print('下载完成，用时: %.2f秒！' % (end - start)) #输出下载用时时间
    except:
        print('出现错误，请检查网络是否有问题。')

def Install():
    """安装汉化补丁"""
    import zipfile, os
    from BinFiles import release
    with open("release.zip", "wb") as fileA:
        fileA.write(release)
    fileB = zipfile.ZipFile("release.zip", "r")
    fileB.extractall()
    fileB.close()
    os.remove("release.zip")
    if os.path.exists("Config.old"):
        os.remove("Config.old")

def IsNew():
    """判断是否有更新版本"""
    import requests
    Version = "v1.3.0"
    new_v = requests.get('https://file.drmt.xyz/Games/Key/Planetarian/_SnowGlobe_CHS_patch/_hide/version')
    new_v = str(new_v.content,'utf-8')
    if new_v != Version:
        with open("Config.old","w") as f:
            # 创建一个文件，用于C++判断是否为新版本
            pass
if __name__ == "__main__":
    import sys
    if sys.argv[1] == "-i":
        Install()
    elif sys.argv[1] == "-d":
        Download()
    elif sys.argv[1] == "-v":
        IsNew()
        

