# -*- coding:utf-8 -*-
"""
@author: lijiahe
"""
import re
import random
import urllib2
import datetime
import os
now_time_ms = datetime.datetime.now()       #the current time
now_tims_d = now_time_ms.strftime("%Y-%m-%d")    #the date of today:yyyy-mm-dd
if not os.path.exists(now_tims_d):      #create the file of today
    os.mkdir(now_tims_d)
if not os.path.exists(now_tims_d+"/url"):
    os.mkdir(now_tims_d+"/url")
if not os.path.exists(now_tims_d+"/ProductData"):
    os.mkdir(now_tims_d+"/ProductData")

class media():
    def __init__(self):
        self.base_dir_url = now_tims_d+"/url/"
        self.base_dir_product_data = now_tims_d+"/ProductData/"
        self.url = ""
        self.host = ""
        self.referer = ""
        self.my_headers = [
            'Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2272.118 Safari/537.36',
            "Mozilla/5.0 (Windows NT6.1; WOW63; rv:27.0) Gecko/20100101 Firefox/27.0",
            "Mozilla/5.0 (Windows; U WOW63; Windows NT6.1; en-US; rv:1.9.1.1) Gecko/20091201 Firefox/3.5.6",
            "Mozilla/5.0 (Windows NT 10.0; WOW64; rv:42.0) Gecko/20100101 Firefox/42.0",
            "Mozilla/5.0 (X11; Ubuntu; Linux i689; rv:10.0) Gecko/20100101 Firefox/10.0",
            "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/42.0.2311.135 Safari/537.36 Edge/12.10240",
            "Mozilla/5.0 (Windows NT 8.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/42.0.2311.135 Safari/537.36 Edge/12.10240",
            "Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/37.0.2062.124 Safari/537.36",
            "Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/37.0.2062.124 Safari/537.36"
        ]

    def GetContent(self):
        """
            To get the content of the web page we look through
            
                output:
                    content             the content of the web page
        """
        random_header = random.choice(self.my_headers)
        req = urllib2.Request(self.url)
        req.add_header("User-Agent", random_header)
        req.add_header("Host", self.host)
        req.add_header("Referer", self.referer)
        req.add_header("GET", self.url)
        try:
            html = urllib2.urlopen(req)
            content = html.read()
#            print html.info()
            html.close()
            return content
        except:
            print "Something wrong is happening in get_content!"

    def DealUrlFirst(self, match, all_link):
        """
            Get the first floor url from all links
                input:
                    match           the model
                    all_link        all links of the web page
        """
        counter = 0
        for each_link in all_link:
            model_link = '<a href="(.*)" class="c-3">'
            break_link = '<a href="(.*)" class="c-6">'
            model_name = 'class="c-3">(.*)</a>'
            if re.search(break_link, each_link):
                break
            result_link = re.findall(model_link, each_link)
            result_name = re.findall(model_name, each_link)
#            print len(result_link), len(result_name)
            if len(result_link) > 0:
                if len(result_name) > 0:
                    print >> match, result_link[0]+' '+result_name[0]
                    counter += 1
        print "All the avaliable links is: ", counter

    def GetUrlFirst(self):
        """
            To get the url of the second floor
        """
        self.url = "https://www.taobao.com/"
        self.host = "www.taobao.com"
        self.referer = "https://www.taobao.com/"
        content = self.GetContent()
        __clear__ = '<a href=.*?</a>'
        match = open(self.base_dir_url+"url_first.html", 'w')
        try:
            all_link = re.findall(__clear__, content, re.S)
            print "All links of the web page is: ", len(all_link)
            self.DealUrlFirst(match, all_link)
        except:
            print "Something wrong is happening!"
        finally:
            match.close()
        match.close()

    def DealUrlSecond14(self, match, content):
        """
            To handle something to get the link
                input:
                    match           pointer of file
                    content         the content of the html
        """
        __clear__0 = '<a href="//www.taobao.com/market/.*?</a>'
        __clear__1 = '<dd class="cat-title" data-tag=""><a href=.*?</a></dd>'
        model_break = '<a href="#nogo"></a>'
        try:
            for line in content.split('\n'):
                if re.search(model_break, line):
                    break
                if re.search(__clear__1, line):
                    each_part = '<dd class="cat-title" data-tag="(.*?)</dd>'
                    links = re.findall(each_part, line)
                    for link in links:
                        url_name = '<a href="(.*)">(.*)</a>'
                        result = re.findall(url_name, link)
                        print >> match, result[0][0]+' '+result[0][1].decode('gbk').encode('utf-8')
                elif re.search(__clear__0, line):
                    url_title = '<a href="(.*.php)">(.*)</a>'
                    result = re.findall(url_title, line)
                    if result:
                        if len(result[0][1]) < 10:
                            print >> match, '\n'
                            print >> match, result[0][0]+' '+result[0][1].decode('gbk').encode('utf-8')
        except:
            print 'Something wrong is happening in the GetUrlSecond!'
    
    def DealUrlSecond58(self, match, content):
        __part__ = '<dl class="" data-ext-img="//img.alicdn.com/(.*?)</dl>'
        allPart = re.findall(__part__, content, re.S)
        
        __title__ = '<dt class="clearfix">(.*?)</dt>'
        __content__ = '</dt>(.*?)<textarea'
        __info__ = '<a href=.*?</a>'
        __url__ = '<a href="(.*?)">'
        __name__ = '">(.*?)</a>'
        for part in allPart:
            allTitle = re.findall(__title__, part, re.S)
            print >> match, allTitle[0]
            allContent = re.findall(__content__, part, re.S)
            for temp in allContent:
                allInfo = re.findall(__info__, temp, re.S)
                for info in allInfo:
                    url = re.findall(__url__, info)
                    name = re.findall(__name__, info)
                    print >> match, url[0]+' '+name[0]
            print >> match, '\n\n'
            

    def GetUrlSecond(self):
        """
            To get the url of the third floor
        """
        counter = 0
        file_handler = open(self.base_dir_url+"url_first.html", "r")
        for line in file_handler.readlines():
            url_name = line.strip().split()
            
            self.url = 'http:'+url_name[0]
            if re.search('www.taobao.*', url_name[0]):
                self.host = "www.taobao.com"
            else:
                getHost = re.findall('//(.*?.com)', url_name[0])
                self.host = getHost[0]
                print url_name[1].decode('utf-8').encode('gbk') +':'+ getHost[0]+','+self.url
            self.referer = "https://www.taobao.com/"
            match_txt = open(self.base_dir_url+url_name[1].decode('utf-8').encode('gbk')+'.txt', "w")
            content = self.GetContent()
            print >> match_txt, content
            match_txt.close()
            if (counter < 4):
                match = open(self.base_dir_url+url_name[1].decode('utf-8').encode('gbk'), "w")
                self.DealUrlSecond14(match, content)
                match.close()
            elif (counter > 3 and counter < 8) or (counter > 11 and counter < 16) or (counter > 19 and counter < 24):
                match = open(self.base_dir_url+url_name[1].decode('utf-8').encode('gbk'), "w")
                self.DealUrlSecond58(match, content)
                match.close()
            counter += 1
        file_handler.close()
product = media()
product.GetUrlFirst()
product.GetUrlSecond()