# spbspu-parallel-programming

#Сборка
g++ -std=c++17 -pthread insaf_home_task_1/main.cpp insaf_home_task_1/clicker.hpp -o main

#Размер массива - 200.000.000

#Результат (количество_потоков: время_в_миллисекундах)
1: 465.2 ms
2: 233.6 ms
4: 134.6 ms
8: 140.4 ms
16: 142.4 ms
32: 140.2 ms
64: 140.8 ms
128: 145.6 ms
256: 156.2 ms
512: 168.2 ms
1024: 190.6 ms
<img width="1418" height="689" alt="Снимок экрана от 2026-09-17 22-52-25" src="https://github.com/user-attachments/assets/55f6fde6-64fb-455a-a2b6-1db2dc8e5ce5" />


