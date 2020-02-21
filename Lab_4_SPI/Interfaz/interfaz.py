#-*- coding: cp1252 -*-
import kivy

from kivy.app   import App
from kivy.uix.gridlayout import GridLayout
from kivy.uix.boxlayout import BoxLayout
from kivy.properties import StringProperty,ObjectProperty,NumericProperty
from kivy.uix.textinput import TextInput
from kivy.clock import Clock
import pkgutil
import time
import serial
import struct
package = serial
#for importers,modname,ispkg in pkgutil.iter_modules(package._path_):
#    print ("Found submodule %s (is a package: %s)" % (modname,ispkg))
UART= serial.Serial(port='COM8',baudrate=9600,bytesize=serial.EIGHTBITS,parity=serial.PARITY_NONE,stopbits=serial.STOPBITS_ONE,timeout=None)
valor=''
event=''
event2=''
event3=''
event4=''
event5=''
i=0
lista=[]
class Separador(BoxLayout):
    valor_1 = StringProperty('0')
    valor_2 = StringProperty('0')
    valor_3 = StringProperty('0')
    valor_4 = StringProperty('0')
    valor_5 = StringProperty('0')
    valor_6 = StringProperty('0')
    valor_7 = StringProperty('0')
    valor_8 = StringProperty('0')
    valor_serial =NumericProperty()
    display=ObjectProperty()
    selector=StringProperty('0')
    a=StringProperty('0')
        
    
    def __init__(self):
        global event5
        super(Separador,self).__init__()
        event5 = Clock.schedule_interval(self.contar_1,0.09)

    def contar_1(self,dt):
        UART.flushInput()
        UART.flushOutput()
        entrada=int.from_bytes(UART.read(1),byteorder = 'big',signed = False)
        entrada2=int.from_bytes(UART.read(1),byteorder = 'big',signed = False)
        print (entrada)
        print (entrada2
               )
        self.valor_1= str(entrada)
        self.valor_3= str(entrada2)


    def pausa(self):
        global numero
        numero = numero - 1
        
        if numero <= 1:
            numero = 0 
        elif numero >= 255:
            numero = 255

        envio = numero.to_bytes(1,byteorder = "little", signed = False)
        UART.write(envio)   
        
    def play (self):
        global numero
        numero = numero + 1
        
        if numero <= 1:
            numero = 0 
        elif numero >= 255:
            numero = 255

        envio = numero.to_bytes(1,byteorder = "little", signed = False)
        UART.write(envio)

    
class MainApp(App):
    def process(self):
        global numero
        global envio
        numero = 0
        text = self.root.ids.input.text
        numero = int(text)
        if numero < 1:
            numero = 0 
        elif numero >= 255:
            numero = 255

        envio = numero.to_bytes(1,byteorder = "little", signed = False)
        UART.write(envio)
        
        
    
    def build (self):
        return Separador()

if __name__ == '__main__':
    MainApp().run()


    
