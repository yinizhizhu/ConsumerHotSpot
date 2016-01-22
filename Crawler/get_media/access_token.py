# -*- coding:utf-8 -*-
"""
@author: lijiahe
"""

#class GetAccessToken:
#    def __init__(self):
#        self.APP_KEY = ['1191410089','893373852','2268480788','2263483240','3832832650','2408287549'] # app key
#        self.APP_SECRET = ['7b3fa597b3dbfacdac3163296ff0a7d7','3f4a4eb2490117c49a472a315deac2df','fe21eb70cac33d3e541f9fb8abcea60a','626ae36d80f9c172332c6d21678a49e5','a650b095e8cd41869714d00b9ed66caf','db6925986ce1e4d98552950a372f5167'] # app secret
#        self.CODE = ['e92a00f4b2396ae0da48552d20bed64b','3e710416a285c81b0aad03486db865a7','5e879781e83a9672e115159d4131bd16','2d897d8e4c780181e54c1e922c289bd2','36efe5fa87c29dd150a9b679ef701c60','ba7fa1898bd1453e3eb4d15135b797ca']
#        self.CALLBACK_URL = 'https://api.weibo.com/oauth2/default.html' # callback url
#        self.printAccessToken()
#    
#    def printAccessToken(self):
#        for i in xrange(6):
#            try:
#                client = APIClient(app_key=self.APP_KEY[i], app_secret=self.APP_SECRET[i], redirect_uri=self.CALLBACK_URL)
#                r = client.request_access_token(self.CODE[i])
#                access_token = r.access_token # 新浪返回的token，类似abc123xyz456
#                expires_in = r.expires_in # token过期的UNIX时间：http://zh.wikipedia.org/wiki/UNIX%E6%97%B6%E9%97%B4
#                client.set_access_token(access_token, expires_in)
#                print client.access_token
#            except:
#                print "Something is wrong in the " + str(i+1)+"!!!!"
#
#start = GetAccessToken()


from weibo import APIClient
APP_KEY = ['1191410089','893373852','2268480788','2263483240','3832832650','2408287549'] # app key
APP_SECRET = ['7b3fa597b3dbfacdac3163296ff0a7d7','3f4a4eb2490117c49a472a315deac2df','fe21eb70cac33d3e541f9fb8abcea60a','626ae36d80f9c172332c6d21678a49e5','a650b095e8cd41869714d00b9ed66caf','db6925986ce1e4d98552950a372f5167'] # app secret
CODE = ['93ff4db778ebd1460a001272030917ce','9758f8803c960153c6dc61191ae01298','6ef0a5128b3be136336745c44d084d01','2f602243a6e62455ab66802352c00614','bfa499f41ba425d7ae9755cc6ba2e0da','399468231574febf69cfdd7e9bbee793']
CALLBACK_URL = 'https://api.weibo.com/oauth2/default.html' # callback url
for i in xrange(6):
    client = APIClient(app_key=APP_KEY[i], app_secret=APP_SECRET[i], redirect_uri=CALLBACK_URL)
    r = client.request_access_token(CODE[i])
    access_token = r.access_token
    expires_in = r.expires_in
    client.set_access_token(access_token, expires_in)
    print client.access_token