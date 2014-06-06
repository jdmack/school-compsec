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
d_f = find_student_file('.',"d.html")
e_f = find_student_file('.',"e.txt")
rd_f = find_student_file('.',"README")

if sid_f == None:
    print "Unable to find SID file!"
    exit(1)
if d_f == None:
    print "Unable to find d.html file!"
    exit(1)
if e_f == None:
    print "Unable to find e.txt file!"
    exit(1)

if rd_f == None:
    print "*NO* README found, handing in without a README.(Not required)"

fsid = open(sid_f,'r')
lines = fsid.readlines()
sid = [line for line in lines if line.strip()][0].strip().replace(" ","_")

print "Submitting these files:"
print sid_f
print d_f
print e_f
if rd_f != None:
    print rd_f
print "With this SID:\""+sid+"\""


inp = raw_input("Are these the files/SID you want to turn in? (Yes/No)")

if inp == "Yes":
    #package
    print "Packaging up your turnin..."

    dirname = "TURNIN_PP3P2_"+sid
    if os.path.exists(dirname):
        print "Removing old turnin directory"
        shutil.rmtree(dirname)
    if os.path.exists(dirname+".tar.gz"):
        print "Removing old turnin .tar.gz"
        os.remove(dirname+".tar.gz")
    os.mkdir(dirname)
    shutil.copy("./"+sid_f,"./"+dirname)
    shutil.copy("./"+d_f,"./"+dirname)
    shutil.copy("./"+e_f,"./"+dirname)
    if rd_f != None:
        shutil.copy("./"+rd_f,"./"+dirname)
    time.sleep(1)
    os.system("tar -czvf "+dirname.strip()+".tar.gz "+dirname)
    print "Sending files..."
    r = os.system("printf \"pp3handin\\nput "+dirname+".tar.gz\\n\" | ftp -v -p redemption.ucsd.edu | grep successfully")
    if r != 0:
        print "\n****ERROR Occurred during FTP upload. Please check network connectivity before contacting a TA."
    else:
        print "\nSuccess! Your turnin has been received!"
else:
    print "Turnin CANCELED. No files were sent."
