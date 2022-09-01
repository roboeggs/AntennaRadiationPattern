import tkinter as tk
import serial.tools.list_ports
import re
import matplotlib.pyplot as plt
import numpy as np
import serial
from tkinter import ttk
from tkinter import * 
from tkinter import messagebox 
import time


port = ''

# построение диаграммы  
def plotting(theta, rssi):
    plt.figure(figsize=(10, 10))        #меняем график в дюймах
    plt.polar(theta, rssi)   # уравнение розы
    plt.show()

# получаем данные Rssi c esp через serial
def getRssi(mode):
    ser = serial.Serial()
    ser.baudrate = 115200
    ser.port = port
    ser.open()
    ser.write(bytes(mode, 'utf-8'))
    line = ""
    #time.sleep(8) # Сон в секунды
    while True:
        rep = ser.read(1).decode('utf-8')
        if rep == "\n":
            break
        if rep != "\r":
            line += rep
        time.sleep(0.001)


    sep = '-'
    result = [sep+x for x in line.split(sep)]
    result.pop(0)
    ser.close()
    print(line)
    return result

# возвращаем список портов
def getPort():
    return list(serial.tools.list_ports.comports())

# обновляем список портов в Combobox
def updtcblist():
    list = getPort()
    comboExample['values'] = list

# после выбора порта указываем его для serial
def callbackFunc(event):
    global port
    country = event.widget.get()
    port = ''.join(re.findall(r"\(([A-Za-z0-9_]+)\)", country))

# автоматический способ получения данных
def autoMode():
    rssi = getRssi("auto\n")
    #print(rssi)
    n = 360 / len(rssi)
    theta = np.arange(0., 2., n/180.)*np.pi
    plotting(theta, rssi)

# вывод значения
def clicked():  
    messagebox.showinfo('Rssi', getRssi("manual\n"))  

app = tk.Tk() 
app.geometry("700x300")

# текст сверху
labelTop = tk.Label(app, text = "Serial port")
labelTop.grid(column=0, row=0)

# список для вывода доступных serial ports
comboExample = ttk.Combobox(app, width=80, height=5, postcommand = updtcblist)
comboExample.grid(column=0, row=1)
comboExample.current()
 

autoGet = Button(app, text="Auto mode", command=autoMode)
autoGet.grid(column=0, row=2)

manual = Button(app, text="Read values", command=clicked)
manual.grid(column=1, row=1) 

comboExample.bind("<<ComboboxSelected>>", callbackFunc)

app.mainloop()