import os
import psutil
import time
import random 
import matplotlib.pyplot as plt

memory_used_array_dc = []
memory_used_array_dp = []
time_required_dc = []
size_of_input_dc = []
time_required_dp = []
size_of_input_dp = []

def profileDC(X, Y, report=False):
    process = psutil.Process(os.getpid())
    startTime = time.process_time()
    result = os.system(r"./align " + X + " " + Y) #ADD YOUR INPUT STRING GENERATOR HERE 
    execution_time = (time.process_time() - startTime)
    memory_used = int(process.memory_info().rss / 1024)
    size_of_input_dc.append(len(X) + len(Y))
    time_required_dc.append(execution_time)
    memory_used_array_dc.append(memory_used)
    return (len(X) + len(Y), execution_time, memory_used)

def profileDP(X, Y, report=False):
    process = psutil.Process(os.getpid())
    startTime = time.process_time()
    result = os.system(r"./dp " + X + " " + Y) #ADD YOUR INPUT STRING GENERATOR HERE 
    execution_time = (time.process_time() - startTime)
    memory_used = int(process.memory_info().rss / 1024)
    size_of_input_dp.append(len(X) + len(Y))
    time_required_dp.append(execution_time)
    memory_used_array_dp.append(memory_used)
    return (len(X) + len(Y), execution_time, memory_used)

if __name__ == '__main__':
    lengths= [5,10,20,50,100,1000,2000,4000,5000,10000, 20000, 50000, 100000, 200000]
    char_array= ["A","C","G","T"]
    string1_array= []
    string2_array= []

    for i in range(len(lengths)): 
        string1_array.append(''.join(random.choice(char_array) for _ in range(lengths[i])))
        string2_array.append(''.join(random.choice(char_array) for _ in range(lengths[i])))
        profileDC(string1_array[i],string2_array[i])
        profileDP(string1_array[i],string2_array[i])
    

    plt.plot(size_of_input_dc, time_required_dc, color="blue")
    plt.plot(size_of_input_dp, time_required_dp, color="red")
    plt.xlabel('Input size')
    plt.ylabel('Time')
    plt.title('Time vs Input size')
    plt.show()

    plt.plot(size_of_input_dc, memory_used_array_dc, color="blue")
    plt.plot(size_of_input_dp, memory_used_array_dp, color="red")
    plt.xlabel('Input size')
    plt.ylabel('Memory')
    plt.title('Memory vs Input size')
    plt.show()

    

