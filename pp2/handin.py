#!/usr/bin/python
import shutil
import os
import time

def find_student_file(d,f):
    for (dirpath,dirnames,filenames) in os.walk(d):
        for fn in filenames:
            if fn == f:
                return os.path.join(dirpath,fn)

    return None

sid_f = find_student_file('.',"SID")
sploit_f = find_student_file('.',"sploit.py")
key_f = find_student_file('.',"key")
wr_f = find_student_file('.',"writeup.txt")

if sid_f == None:
    print "Unable to find SID file!"
    exit(1)
if sploit_f == None:
    print "Unable to find sploit.py file!"
    exit(1)
if key_f == None:
    print "Unable to find key file!"
    exit(1)
if wr_f == None:
    print "Unable to find writeup.txt file!"
    exit(1)
    
fsid = open(sid_f,'r')
lines = fsid.readlines()
sid = [line for line in lines if line.strip()][0].strip().replace(" ","_")

print "Submitting these files:"
print sid_f
print sploit_f
print key_f
print wr_f
print "With this SID:\""+sid+"\""


inp = raw_input("Are these the files/SID you want to turn in? (Yes/No)")

if inp == "Yes":
    #package
    print "Packaging up your turnin..."

    dirname = "TURNIN_"+sid
    if os.path.exists(dirname):
        print "Removing old turnin directory"
        shutil.rmtree(dirname)
    if os.path.exists(dirname+".tar.gz"):
        print "Removing old turnin .tar.gz"
        os.remove(dirname+".tar.gz")
    os.mkdir(dirname)
    shutil.copy("./"+sid_f,"./"+dirname)
    shutil.copy("./"+sploit_f,"./"+dirname)
    shutil.copy("./"+key_f,"./"+dirname)
    shutil.copy("./"+wr_f,"./"+dirname)
    time.sleep(1)
    os.system("tar -czvf "+dirname.strip()+".tar.gz "+dirname)
    print "Sending files..."
    r = os.system("printf \"pp2handin\\nput "+dirname+".tar.gz\\n\" | ftp -v -p redemption.ucsd.edu | grep successfully")
    if r != 0:
        print "\n****ERROR Occurred during FTP upload. Please check network connectivity before contacting a TA."
    else:
        print "\nSuccess! Your turnin has been received!"
else:
    print "Turnin CANCELED. No files were sent."
