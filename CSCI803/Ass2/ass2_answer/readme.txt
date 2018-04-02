At first, I'd like to introduce my program a little bit. I only use algorithms whose O(n) is logn, such as siftup and siftdown, even when I need to find the shortest queue in multi-queue simulation. That part is a little complicated.

You just need to put the code file "CSCI803_ass2_YixiangFan_5083898.cpp" and the input sample files in the same folder. Then compile the code file. In ubuntu, for example, the command is "g++ -o out CSCI803_ass2_YixiangFan_5083898.cpp". Then execute the file out, using the following command : ./out

When the program is running , you will be asked to input the data file name. So input the , for example, ass2_sample_input. Then you will get the result as follow :

Please input file name : ass2_sample_input
Single queue : 
The number of customers : 1000
The finishing time : 30558.395
The average service time : 159.108
The average time a customer spends in queue : 0.154
The maximum time a customer spends in queue : 39.693
The average length of queue : 0.005
The maximum length of queue : 2
        Total idle time for server 1 : 14933.395
        Total idle time for server 2 : 12873.889
        Total idle time for server 3 : 18306.145
        Total idle time for server 4 : 13461.205
        Total idle time for server 5 : 16237.428
        Total idle time for server 6 : 10322.134
        Total idle time for server 7 : 13223.199
        Total idle time for server 8 : 14810.663
        Total idle time for server 9 : 12289.018
        Total idle time for server 10 : 14631.493
Multi queue : 
The number of customers : 1000
The finishing time : 30558.395
The average service time : 159.108
The average time a customer spends in all queue : 0.638
The maximum time a customer spends in all queue : 188.355
The average length of all queue : 0.002
        The average length of queue 1 : 0.000
        The average length of queue 2 : 0.000
        The average length of queue 3 : 0.002
        The average length of queue 4 : 0.000
        The average length of queue 5 : 0.000
        The average length of queue 6 : 0.005
        The average length of queue 7 : 0.001
        The average length of queue 8 : 0.002
        The average length of queue 9 : 0.000
        The average length of queue 10 : 0.011
The maximum length of all queue : 2
        The maximum length of queue 1 : 0
        The maximum length of queue 2 : 0
        The maximum length of queue 3 : 1
        The maximum length of queue 4 : 0
        The maximum length of queue 5 : 0
        The maximum length of queue 6 : 1
        The maximum length of queue 7 : 1
        The maximum length of queue 8 : 1
        The maximum length of queue 9 : 0
        The maximum length of queue 10 : 2
Total idle time for server 1 : 11473.695
Total idle time for server 2 : 14068.089
Total idle time for server 3 : 16111.145
Total idle time for server 4 : 13509.105
Total idle time for server 5 : 17669.728
Total idle time for server 6 : 14065.034
Total idle time for server 7 : 14812.499
Total idle time for server 8 : 13890.463
Total idle time for server 9 : 11114.518
Total idle time for server 10 : 14253.393
