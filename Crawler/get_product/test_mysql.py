#-*- encoding: utf-8 -*-
import sys
import MySQLdb

# connect the database
try:
    conn = MySQLdb.connect(host='localhost',user='',passwd='',db='test')
except Exception, e:
    print e
    sys.exit()

# get object cursor to operate

cursor = conn.cursor()
# create table
sql = "create table if not exists test1(name varchar(128) primary key, age int(4))"
cursor.execute(sql)
# insert the data
sql = "insert into test1(name, age) values ('%s', %d)" % ("zhaowei", 23)
try:
    cursor.execute(sql)
except Exception, e:
    print e

sql = "insert into test1(name, age) values ('%s', %d)" % ("张三", 21)
try:
    cursor.execute(sql)
except Exception, e:
    print e
# insert multi data

sql = "insert into test1(name, age) values (%s, %s)"
val = (("李四", 24), ("王五", 25), ("洪六", 26))
try:
    cursor.executemany(sql, val)
except Exception, e:
    print e

# to search info
sql = "select * from test1"
cursor.execute(sql)
alldata = cursor.fetchall()
# alldata is two dimensions
if alldata:
    for rec in alldata:
        print rec[0].decode('utf-8').encode('gbk'), rec[1]

cursor.close()

conn.close()
