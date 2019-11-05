# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
import requests
import os

from bs4 import BeautifulSoup

root='D://openlab//pic_from_4399//'#存放图片的根目录
suffix='.jpg'#文件后缀
file='D://openlab//重复游戏.txt'#用于存放重复出现的游戏名称
url1='http://www.4399.com/'#目标网址

#申请并解析
r=requests.get(url1)
r.encoding=r.apparent_encoding 
soup=BeautifulSoup(r.text,'html.parser') 
#创建目录
if not os.path.exists(root):
    os.mkdir(root)
with open(file,'w') as f1:#用来记录重复的游戏
    
    try:
        for tag in soup.find_all('img'):  
            
            if 'alt' in tag.attrs:
                
                if 'src' in tag.attrs:                   
                    url=tag.attrs['src']
                    r1=requests.get(url)
                    path=root+str(tag.attrs['alt'])+suffix
                    
                    
                    
                    if not os.path.exists(path):
                        with open(path,'wb') as f:
                            f.write(r1.content)
                            f.close()
                    else:
                        #print('文件已存在')
                        f1.write(str(tag.attrs['alt']))
                        f1.write('\n')
                        
                        
                elif 'lz_src' in tag.attrs:
                    
                    #print(tag.attrs['src'])
                    url=tag.attrs['lz_src']
                    r1=requests.get(url)
                        
                    path=root+str(tag.attrs['alt'])+suffix                        
                    if not os.path.exists(path):
                        with open(path,'wb') as f:
                            f.write(r1.content)
                            f.close()
                    else:
                                #print('文件已存在')
                            f1.write(str(tag.attrs['alt']))
                            f1.write('\n')
                            
                elif 'name' in tag.attrs :
                     
                     
                    url=tag.attrs['name']
                    r1=requests.get(url)
                     
                    path=root+str(tag.attrs['alt'])+suffix
                     
                    if not os.path.exists(path):
                                 
                        with open(path,'wb') as f:
                            f.write(r1.content)
                            f.close()
                    else:
                        f1.write(str(tag.attrs['alt']))
                        f1.write('\n')
                     
                    
                    
                     
                            
                            
                            
                            
            elif tag.text:
                url=tag.attrs['lz_src']
                r1=requests.get(url)
                
                path=root+tag.text+suffix
                if not os.path.exists(root):
                    os.mkdir(root)
                if not os.path.exists(path):
                    with open(path,'wb') as f:
                        f.write(r1.content)
                        f.close()
                else:
                    #print('文件已存在')
                    f1.write(str(tag.text))
                    f1.write('\n')
                    
    
           
    except:
        print('无法爬取')
        
print('Finish')
        
