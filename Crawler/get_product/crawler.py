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
            print html.info()
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
        match = open(self.base_dir_url+"url_first.html", "w")
        try:
            all_link = re.findall(__clear__, content, re.S)
            print "All links of the web page is: ", len(all_link)
            self.DealUrlFirst(match, all_link)
        except:
            print "Something wrong is happening!"
        finally:
            match.close()
        match.close()

    def DealUrlSecond(self, match_txt, match, content):
        """
            To handle something to get the link
                input:
                    match_txt       the pointer of the html file
                    match           pointer of file
                    content         the content of the html
        """
        __clear__0 = '<a href="//www.taobao.com/market/.*?</a>'
        __clear__1 = '<dd class="cat-title" data-tag=""><a href=.*?</a></dd>'
        model_break = '<a href="#nogo"></a>'
        try:
            for line in match_txt.readlines():
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

    def GetUrlSecond(self):
        """
            To get the url of the third floor
        """
        file_handler = open(self.base_dir_url+"url_first.html", "r")
        for line in file_handler.readlines():
            url_name = line.strip().split()
            match_txt = open(self.base_dir_url+url_name[1].decode('utf-8').encode('gbk')+'.txt', "w")
            self.url = 'https:'+url_name[0]
            if re.search('www.taobao.*', url_name[0]):
                self.host = "www.taobao.com"
            else:
                self.host = 'www.jiyoujia.com'
            self.referer = "https://www.taobao.com/"
            content = self.GetContent()
            if content:
                print >> match_txt, content
                match_txt.close()
                match_txt = open(self.base_dir_url+url_name[1].decode('utf-8').encode('gbk')+'.txt', "r")
                match = open(self.base_dir_url+url_name[1].decode('utf-8').encode('gbk'), "w")
                self.DealUrlSecond(match_txt, match, content)
                match.close()
                match_txt.close()
        file_handler.close()
product = media()
product.GetUrlFirst()
product.GetUrlSecond()