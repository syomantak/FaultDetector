
import numpy as np
import matplotlib.pyplot as plt
import os

alpha = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']
words = [x+y for x in alpha for y in alpha]


logic = {"AND_2":"&" , "OR_2":"|" , "INVERTER":"!" , "XOR_2":"^" , "NAND_2":"." , "NOR_2":"%"}
vals = {}
name_to_node = {}

def file_len(fname):
    with open(fname) as f:
        for i,l in enumerate(f):
            pass

    return i + 1

flen = file_len("input.txt")
f = open("input.txt",'r')

## LINE 1
in_nodes = [x.strip() for x in (f.readline()).split(' ')]
num_in = int(in_nodes[0])

for j in range(int(num_in)):
    name_to_node[in_nodes[j+1]] = words[j]
    vals[words[j]] = words[j]

inter_node_count = num_in

## LINE 2
fault = f.readline()
fault = [x.strip() for x in fault.split(' ')]

fault_name = fault[0]

fault_condn = fault[1]

net_output_name = fault[2]


for _ in range(flen-2):     
    itr = f.readline()
    itr = [x.strip() for x in itr.split('(')]
    

    cmd = itr[0]

    itr = [x.strip() for x in itr[1].split(',')]

    if(cmd=='INVERTER'):

        cmd = logic[cmd]

        in1 = itr[0]
        out = [x.strip() for x in itr[1].split(')')]
        out = out[0]
        
        in1 = name_to_node[in1]
        
        name_to_node[out] = words[inter_node_count]
        inter_node_count = inter_node_count + 1
        out = name_to_node[out]


        vals[out] = "[!"+","+vals[in1]+"]"

    else:    

        cmd = logic[cmd]

        in1 = itr[0]
        in2 = itr[1]
        out = [x.strip() for x in itr[2].split(')')]
        out = out[0]


        in1 = name_to_node[in1]

        in2 = name_to_node[in2]
        

        name_to_node[out] = words[inter_node_count]
        inter_node_count = inter_node_count + 1
        out = name_to_node[out]
  

        vals[out] = "["+vals[in1]+","+cmd+","+vals[in2]+"]"


f.close()

fault_node = name_to_node[fault_name]
net_output_node = name_to_node[net_output_name]



f = open("input.txt",'r')
f.readline()
f.readline()


flt = {}
for j in range(int(num_in)):
    flt[words[j]] = words[j]

### CHECK
if(fault_condn=='1'):
    flt[fault_node]='1'

if(fault_condn=='0'):
    flt[fault_node]='0'

inter_node_count = num_in

for _ in range(flen-2):
    itr = f.readline()
    itr = [x.strip() for x in itr.split('(')]
    

    cmd = itr[0]

    itr = [x.strip() for x in itr[1].split(',')]

    if(cmd=='INVERTER'):

        cmd = logic[cmd]

        in1 = itr[0]
        out = [x.strip() for x in itr[1].split(')')]
        out = out[0]

        in1 = name_to_node[in1]
        
        name_to_node[out] = words[inter_node_count]
        inter_node_count = inter_node_count + 1
        out = name_to_node[out]

        if(out==fault_node):
            continue


        flt[out] = "[!"+","+flt[in1]+"]"

    else:    
        cmd = logic[cmd]

        in1 = itr[0]
        in2 = itr[1]
        out = [x.strip() for x in itr[2].split(')')]
        out = out[0]

        in1 = name_to_node[in1]
        in2 = name_to_node[in2]
        

        name_to_node[out] = words[inter_node_count]
        inter_node_count = inter_node_count + 1
        out = name_to_node[out]


        if(out == fault_node):
            continue


        flt[out] = "["+flt[in1]+","+cmd+","+flt[in2]+"]"

f.close()

'''
for x in vals:
    print(x+" - "+vals[x])

for x in flt:
    print(x+" - "+flt[x])
'''
f_ = vals[net_output_node]
fh = flt[net_output_node]

net_f = "["+f_+",^,"+fh+"]"

f = open(".temp_comm","w")
#print(net_f)
f.write(net_f)
f.write("\n")
f.write(str(num_in)+"\n")
for j in range(num_in):
    f.write(in_nodes[j+1]+" "+words[j]+"\n")

f.close()

os.system('g++ -std=c++14 -o ex sat_solver.cpp')
os.system('./ex < .temp_comm')
os.system('rm .temp_comm')
os.system('rm ex')
