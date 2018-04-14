# This project requires PyBluez
from tkinter import *
import bluetooth
# -*- coding: utf-8 -*-
#Look for all Bluetooth devices
#the computer knows about.
print("Searching for devices...")
print("")
#Create an array with all the MAC
#addresses of the detected devices
nearby_devices = bluetooth.discover_devices()
#Run through all the devices found and list their name
num = 0
print("Select your device by entering its coresponding number...")
for i in nearby_devices:
	num+=1
	print(num , ": " , bluetooth.lookup_name( i ))

#Allow the user to select their Arduino
#bluetooth module. They must have paired
#it before hand.
selection = int(input("> ")) - 1
print("You have selected", bluetooth.lookup_name(nearby_devices[selection]))
bd_addr = nearby_devices[selection]

port = 1

#Create the GUI
class Application(Frame):

#Create a connection to the socket for Bluetooth
#communication
    sock = bluetooth.BluetoothSocket( bluetooth.RFCOMM )

    def disconnect(self):
    	#Close socket connection to device
        self.sock.close()
        
    def on(self):
    	#Send 'H' which the Arduino
    	#detects as turning the light on
        data = "w"
        self.sock.send(data)

    def off(self):
    	#Send 'L' to turn off the light
    	#attached to the Arduino
        data = "L"
        self.sock.send(data)
        
    def throttle(self, amount):
        #TODO: Have throttle slider on GUI smoothly change speed variable on Arduino
        data = amount
        self.sock.send(data)

    def createWidgets(self):
    	#Form all the buttons.
    	#Look at a Tkinter reference
    	#for explanations.
        self.throttle = Scale(self, from_=100, to=0)
        
        self.QUIT = Button(self)
        self.QUIT["text"] = "QUIT"
        self.QUIT["fg"]   = "red"
        self.QUIT["command"] =  self.quit

        self.disconnectFrom = Button(self)
        self.disconnectFrom["text"] = "Disconnect"
        self.disconnectFrom["fg"]   = "darkgrey"
        self.disconnectFrom["command"] =  self.disconnect

        self.turnOn = Button(self)
        self.turnOn["text"] = "On",
        self.turnOn["fg"] = "green"
        self.turnOn["command"] = self.on

        self.turnOff = Button(self)
        self.turnOff["text"] = "Off"
        self.turnOff["fg"] = "red"
        self.turnOff["command"] = self.off
        
        self.throttle2 = Scale(self, from_=100, to=0)
        
        self.throttle.grid(column=0, row=0)
        self.QUIT.grid(column=1, row=1)
        self.disconnectFrom.grid(column=2, row=1)
        self.turnOn.grid(column=3, row=1)
        self.turnOff.grid(column=4, row=1)
        self.throttle2.grid(column=5, row=0)

    def __init__(self, master=None):
    	#Connect to the bluetooth device
    	#and initialize the GUI
        self.sock.connect((bd_addr, port))
        Frame.__init__(self, master)
        self.grid(sticky=N+S+E+W)
        self.createWidgets()

#Begin the GUI processing
root = Tk()
root.title('Super Car 9000 GUI')
app = Application(root)
app.mainloop()
root.destroy()