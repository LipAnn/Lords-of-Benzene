import os
import re



files = os.listdir(os.curdir)
h_sample = re.compile('".+\.h"')
cpp_sample = re.compile("^.+\.cpp$")
cpp_files = [file for file in files if cpp_sample.match(file) is not None]
o_files = [file[:-3] + "o" for file in cpp_files]

h_files = dict()
for file in cpp_files:
    fin = open(file, "r")
    h_f = []
    cnt = 10
    cur = 0
    while True:
        text = fin.readline().strip()
        #print (text)
        if not text:
            cur += 1
        if cur == cnt:
            break
        if text and text[0] != '#':
            break
        h_f += h_sample.findall(text)
    for i in range(len(h_f)):
        h_f[i] = h_f[i][1:-1]
    fin.close()
    h_files[file] = h_f

makefile = open("Makefile", "w")

print("OBJECTS=" + " ".join(o_files), file=makefile)
print("CC=g++", file=makefile)
print("CFLAGS= -std=gnu++11 `pkg-config opencv --cflags` -O2", file=makefile)
print("CLIBS=`pkg-config opencv --libs` -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_flann -lopencv_nonfree", file=makefile)
print("all : main", file=makefile)
print("main : $(OBJECTS)", file=makefile)
print("\t$(CC) $(CFLAGS) $^ $(CLIBS) -o $@", file=makefile)
for idx, o_file in enumerate(o_files):
    print(o_file + " : " + cpp_files[idx] + " " + " ".join(h_files[cpp_files[idx]]), file=makefile)
    print ("\t$(CC) $(CFLAGS) -c $< $(CLIBS) -o $@", file=makefile)
print("clean :", file=makefile)
print("\trm -f *.o main", file=makefile)

makefile.close()
