# -*- coding:utf-8 -*-
"""
@author: lijiahe
"""
import os
import re
import gc
import time
import json
import urllib2
import datetime

basedir = "MediaData"
if not os.path.exists(basedir):      #create the file of today
    os.mkdir(basedir)

now_time_ms = datetime.datetime.now()
filename = basedir + '/' + now_time_ms.strftime("%Y-%m-%d") + '.txt'
#create = open(filename, 'w')
#create.close()

class MediaData:
    def __init__(self):
        self.weibos = ""
        self.file = filename
        self.my_urls = ['https://api.weibo.com/2/statuses/public_timeline.json?access_token=2.00qkLk3DlLCdSB2c7177e71f05YSwG&count=15',
               'https://api.weibo.com/2/statuses/public_timeline.json?access_token=2.00qkLk3D0g2V9y0857b3e022pBFalD&count=15',
               'https://api.weibo.com/2/statuses/public_timeline.json?access_token=2.00qkLk3DoT_WTC1db01ead6f4yEB2C&count=15',
               'https://api.weibo.com/2/statuses/public_timeline.json?access_token=2.00qkLk3DM52LTC4f286076e9rHacqB&count=15',
               'https://api.weibo.com/2/statuses/public_timeline.json?access_token=2.00qkLk3D9rK5LE384eaae769b3kU3E&count=15',
               'https://api.weibo.com/2/statuses/public_timeline.json?access_token=2.00qkLk3DZbvycC7843f50aeapiFmbC&count=15']
    
    def getWeibo(self, position):
        url = self.my_urls[position % 6]
        html = urllib2.urlopen(url)
        content = html.read()
        __clear__ = '{"statuses":(.*?),"hasvisible":'
        data = re.findall(__clear__, content)
        self.weibos = data[0]
    
    def unicode_utf8(self, src):
        result = ''
        for x in src:
            try:
                x = x.encode("utf-8")
            except:
                print "Cannot encode the words!"
                x = ""
            result += x
        return result
     
    def outputWeibo(self):
        weibos_list = json.loads(self.weibos)
        output = open(self.file, "a")
        des = "text"
        for weibo in weibos_list:
            print >> output, self.unicode_utf8(weibo[des])
            print >> output, '\n'
        output.close()
    
    #    TEST = open("content.txt", "w")
    #    print >> TEST, weibos
    #    TEST.close()
if __name__ == '__main__':
    i = 1
    weibo = MediaData()
    while (True):
        start = time.clock()
        while (True):
            end = time.clock()
            if (end - start > 2.1):
#                print end-start
                break
        try:
            weibo.getWeibo(i)
            weibo.outputWeibo()
            print i
            i += 1
        except:
            print str(i)+": Something Wrong!"
            i += 1