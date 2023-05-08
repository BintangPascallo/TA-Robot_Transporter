# Libraries
import customtkinter as ctk
import os
from PIL import ImageTk,Image  
import signal
import tkinter as tk

# Call Class
# from font_style import *
# from splashscreen import *
# from menu import *

# Main Class
class MainApp(ctk.CTk):
    def __init__(self):
        super().__init__()
        
        # Configuration
        self.attributes('-topmost', 1)
        self.resizable(False, False)
        self.configure(bg='black')
        self.title('Robot Transporter')
        # self.overrideredirect(True) # or 1 instead of True
        # self.window.iconbitmap('./assets/pythontutorial.ico')
        
        # Get The Screen Dimension
        self.window_width = 800
        self.window_height = 480
        self.screen_width = self.winfo_screenwidth()
        self.screen_height = self.winfo_screenheight()
        
        # Find The Center Point
        self.center_x = int(self.screen_width/2 - self.window_width / 2)
        self.center_y = int(self.screen_height/2 - self.window_height / 2)
        
        # Set Window To Center
        self.geometry(f'{self.window_width}x{self.window_height}+{self.center_x}+{self.center_y}')
        
        # Column
        self.columnconfigure(0, weight = 0)
        
        # Frame
        self._frame = None
        self.switch_frame(SplashScreenFrame) # SplashScreenFrame
        self.after(3000, lambda : self.switch_frame(MainMenuFrame)) 
        
    # Swith Frame Logic
    def switch_frame(self, frame_class):
        # Declare New Frame
        new_frame = frame_class(self)
        
        # Destroy The Frame
        if self._frame is not None:
            self._frame.destroy()
            
        self._frame = new_frame
        self._frame.pack(expand = True, fill = "both")
        
        # tk.Label(self, text="This is the start page").pack(side="top", fill="x", pady=10)
        # tk.Button(self, text="Open page one",
        #         command=lambda: master.switch_frame(PageOne)).pack()
        # tk.Button(self, text="Open page two",
        #         command=lambda: master.switch_frame(PageTwo)).pack()
        
# Splash Screen Class
class SplashScreenFrame(ctk.CTkFrame):
    def __init__(self,  master, **kwargs):
        super().__init__(master, **kwargs)
        
        # Frame Configuration
        self.configure(fg_color = 'black')
        
        # Create Splash Screen Label
        title = ctk.CTkLabel(
            self,
            text = 'Robot Transporter',
            font = ("Kemco Pixel", 40),
            text_color = "#F7AC13"
        )
        
        title.place(relx = 0.5, rely = 0.7, anchor = 'center')
        
        # Image Assets
        logo_assets = ctk.CTkImage(light_image = Image.open(
            '/home/bintangpascallo/GUI_robot/Assets/images/logo.png'
            ),size = (150, 150))
        
        logo_image = ctk.CTkLabel(
            self,
            text = '',
            image = logo_assets, 
        )
        
        logo_image.place(relx = 0.5, rely = 0.35, anchor = 'center')
        
        
# Auto Manual Class
class MainMenuFrame(ctk.CTkFrame):
    def __init__(self,  master, **kwargs):
        super().__init__(master, **kwargs)
        
        # Frame Configuration
        self.configure(fg_color = 'black')
        
        # Create Title
        title_mainmenu = ctk.CTkLabel(
            self,
            text = 'Main Menu',
            font = ("Kemco Pixel", 50),
            text_color = "#F7AC13"
        )
        
        title_mainmenu.place(relx = 0.5, rely = 0.1, anchor = 'center')
        
        # Create Back Button Configuration
        image_exit = ctk.CTkImage(light_image = Image.open(
            '/home/bintangpascallo/GUI_robot/Assets/images/ButtonBack.png'
            ),size = (45, 45))
        
        button_manual = ctk.CTkButton(
            self,
            fg_color = 'black',
            image = image_exit,
            text = '',
            width = 45,
            height = 45,
            hover_color = '#4E4500', #7A6D00
            command = lambda : tk.messagebox.askretrycancel(
                title='Warning', 
                message='Are You Sure To Exit This Apps?')
            # exit()
            # anchor = "center",
        )
        
        button_manual.place(
            relx = 0.075, rely = 0.1, anchor = 'center',
        )
        
        # Create Launch Button Configuration
        image_launch = ctk.CTkImage(light_image = Image.open(
            '/home/bintangpascallo/GUI_robot/Assets/images/ButtonLaunch.png'
            ),size = (215, 280))
        
        button_launch = ctk.CTkButton(
            self,
            fg_color = 'black',
            image = image_launch,
            text = '',
            # width = 45,
            # height = 45,
            hover_color = '#4E4500', #7A6D00
            command = lambda : master.switch_frame(AutoManualFrame)
            # anchor = "center",
        )
        
        button_launch.place(
            relx = 0.19, rely = 0.55, anchor = 'center',
        )
        
        # Create Setting Button Configuration
        image_setting = ctk.CTkImage(light_image = Image.open(
            '/home/bintangpascallo/GUI_robot/Assets/images/ButtonSetting.png'
            ),size = (215, 280))
        
        button_setting = ctk.CTkButton(
            self,
            fg_color = 'black',
            image = image_setting,
            text = '',
            # width = 45,
            # height = 45,
            hover_color = '#4E4500', #7A6D00
            command = lambda : master.switch_frame(SettingFrame)
            # anchor = "center",
        )
        
        button_setting.place(
            relx = 0.5, rely = 0.55, anchor = 'center',
        )
        
        # Create Help Button Configuration
        image_help = ctk.CTkImage(light_image = Image.open(
            '/home/bintangpascallo/GUI_robot/Assets/images/ButtonHelp.png'
            ),size = (215, 280))
        
        button_help = ctk.CTkButton(
            self,
            fg_color = 'black',
            image = image_help,
            text = '',
            # width = 45,
            # height = 45,
            hover_color = '#4E4500', #7A6D00
            # command = lambda : Roscore()
            # anchor = "center",
        )
        
        button_help.place(
            relx = 0.81, rely = 0.55, anchor = 'center',
        )
        
        # def Roscore():
        #     # os.system('neofetch')
        #     os.system("gnome-terminal -e 'bash -c \"source ~/.bashrc; roscore; exec bash\"'")
        #     # open a file
        #     # file1 = open("/home/bintangpascallo/bash/roscore.sh")
        #     # # read the file
        #     # read_content = file1.read()
        #     # print(read_content)
            
        # def Roscore2():
        #     os.system('rosnode kill --all; killall -9 rosmaster;')
        #     # os.system("gnome-terminal -e 'bash -c \"rosnode kill --all; killall -9 rosmaster; exec bash\"'")
        #     # os.kill(os.getppid(), signal.SIGHUP)

# Setting Class
class SettingFrame(ctk.CTkFrame):
    def __init__(self,  master, **kwargs):
        super().__init__(master, **kwargs)
        
        # Frame Configuration
        self.configure(fg_color = 'black')
        
        # Create Title
        title_setting = ctk.CTkLabel(
            self,
            text = 'Setting',
            font = ("Kemco Pixel", 50),
            text_color = "#F7AC13"
        ).place(relx = 0.5, rely = 0.1, anchor = 'center')
        
        # Create Back Button Configuration
        image_exit = ctk.CTkImage(light_image = Image.open(
            '/home/bintangpascallo/GUI_robot/Assets/images/ButtonBack.png'
            ),size = (45, 45))
        
        button_back = ctk.CTkButton(
            self,
            fg_color = 'black',
            image = image_exit,
            text = '',
            width = 45,
            height = 45,
            hover_color = '#4E4500', #7A6D00
            command = lambda : self.switch_frame(MainMenuFrame) # self.back() 
            # anchor = "center",
        )
        
        button_back.place(
            relx = 0.075, rely = 0.1, anchor = 'center',
        )
        
        # Create Auto Button Configuration
        # image_auto = ctk.CTkImage(light_image = Image.open(
        #     '/home/bintangpascallo/GUI_robot/Assets/images/ButtonAuto.png'
        #     ),size = (250, 300))
        
        # Button Roscore
        button_roscore = ctk.CTkButton(
            self,
            fg_color = 'black',
            text = 'Roscore',
            font = ("Kemco Pixel", 20),
            text_color = "#F7AC13",
            hover_color = '#4E4500', #7A6D00
            border_color = '#F7AC13',
            border_width = 3,
            width = 150,
            height = 150,
            corner_radius = 0,
            command = lambda : os.system("gnome-terminal -e 'bash -c \"source ~/.bashrc; cd; roscore; exec bash\"'")
            # anchor = "center",
        ).place(
            relx = 0.475, rely = 0.425, anchor = 'e',
        )
        
        self._frame = None
    
    # Swicth Frame Logic
    def switch_frame(self, frame_class):
        # Declare New Frame
        new_frame = frame_class(self)
        
        # Destroy The Frame
        if self._frame is not None:
            self._frame.destroy()
            
        self._frame = new_frame
        self._frame.pack(expand = True, fill = "both")  

# Auto Manual Class
class AutoManualFrame(ctk.CTkFrame):
    def __init__(self,  master, **kwargs):
        super().__init__(master, **kwargs)
        
        # Frame Configuration
        self.configure(fg_color = 'black')
        
        # Create Title
        title_automanual = ctk.CTkLabel(
            self,
            text = 'Launch Mode',
            font = ("Kemco Pixel", 50),
            text_color = "#F7AC13"
        )
        
        title_automanual.place(relx = 0.5, rely = 0.1, anchor = 'center')
        
        # Create Back Button Configuration
        image_exit = ctk.CTkImage(light_image = Image.open(
            '/home/bintangpascallo/GUI_robot/Assets/images/ButtonBack.png'
            ),size = (45, 45))
        
        button_back = ctk.CTkButton(
            self,
            fg_color = 'black',
            image = image_exit,
            text = '',
            width = 45,
            height = 45,
            hover_color = '#4E4500', #7A6D00
            command = lambda : self.switch_frame(MainMenuFrame) # self.back() 
            # anchor = "center",
        )
        
        button_back.place(
            relx = 0.075, rely = 0.1, anchor = 'center',
        )
        
        # Create Auto Button Configuration
        image_auto = ctk.CTkImage(light_image = Image.open(
            '/home/bintangpascallo/GUI_robot/Assets/images/ButtonAuto.png'
            ),size = (250, 300))
        
        button_auto = ctk.CTkButton(
            self,
            fg_color = 'black',
            image = image_auto,
            text = '',
            hover_color = '#4E4500', #7A6D00
            command = lambda : self.master.switch_frame(AutoFrame)
            # anchor = "center",
        )
        
        button_auto.place(
            relx = 0.3, rely = 0.55, anchor = 'center',
        )
        
        # Create Manual Button Configuration
        image_manual = ctk.CTkImage(light_image = Image.open(
            '/home/bintangpascallo/GUI_robot/Assets/images/ButtonManual.png'
            ),size = (250, 300))
        
        button_manual = ctk.CTkButton(
            self,
            fg_color = 'black',
            image = image_manual,
            text = '',
            hover_color = '#4E4500', #7A6D00
            command = lambda : self.master.switch_frame(ManualFrame)
            # anchor = "center",
        )
        
        button_manual.place(
            relx = 0.7, rely = 0.55, anchor = 'center',
        )
        
        self._frame = None
    
    # Swicth Frame Logic
    def switch_frame(self, frame_class):
        # Declare New Frame
        new_frame = frame_class(self)
        
        # Destroy The Frame
        if self._frame is not None:
            self._frame.destroy()
            
        self._frame = new_frame
        self._frame.pack(expand = True, fill = "both")  
    
    
# Auto Class
class AutoFrame(ctk.CTkFrame):
    def __init__(self,  master, **kwargs):
        super().__init__(master, **kwargs)
        
        # Frame Configuration
        self.configure(fg_color = 'black')
        
        # Create Title
        title_auto = ctk.CTkLabel(
            self,
            text = 'Auto Mode',
            font = ("Kemco Pixel", 50),
            text_color = "#F7AC13"
        )
        
        title_auto.place(relx = 0.5, rely = 0.1, anchor = 'center')
        
        # Create Message
        title_destination = ctk.CTkLabel(
            self,
            text = 'Choose Your Destination',
            font = ("Kemco Pixel", 25),
            text_color = "#F7AC13"
        )
        
        title_destination.place(relx = 0.5, rely = 0.2, anchor = 'center')
        
        # title_connect_status = ctk.CTkLabel(
        #     self,
        #     text = 'Not Connected',
        #     font = ("Kemco Pixel", 35),
        #     text_color = "#F7AC13"
        # )
        
        # title_connect_status.place(relx = 0.5, rely = 0.6, anchor = 'center')
        
        # Create Back Button Configuration
        image_exit = ctk.CTkImage(light_image = Image.open(
            '/home/bintangpascallo/GUI_robot/Assets/images/ButtonBack.png'
            ),size = (45, 45))
        
        button_back = ctk.CTkButton(
            self,
            fg_color = 'black',
            image = image_exit,
            text = '',
            width = 45,
            height = 45,
            hover_color = '#4E4500', #7A6D00
            command = lambda : self.switch_frame(AutoManualFrame) # self.back() 
            # anchor = "center",
        )
        
        button_back.place(
            relx = 0.075, rely = 0.1, anchor = 'center',
        )
        
        # Button Programming Lab
        button_lab_programming = ctk.CTkButton(
            self,
            fg_color = 'black',
            text = 'Lab\n\nProgram',
            font = ("Kemco Pixel", 20),
            text_color = "#F7AC13",
            hover_color = '#4E4500', #7A6D00
            border_color = '#F7AC13',
            border_width = 3,
            width = 150,
            height = 150,
            corner_radius = 0,
            # command = lambda : self.master.switch_frame(ManualFrame)
            # anchor = "center",
        ).place(
            relx = 0.225, rely = 0.425, anchor = 'e',
        )
        
        # Button Sensorik Lab
        button_lab_sensorik = ctk.CTkButton(
            self,
            fg_color = 'black',
            text = 'Lab\n\nSensorik',
            font = ("Kemco Pixel", 20),
            text_color = "#F7AC13",
            hover_color = '#4E4500', #7A6D00
            border_color = '#F7AC13',
            border_width = 3,
            width = 150,
            height = 150,
            corner_radius = 0,
            # command = lambda : self.master.switch_frame(ManualFrame)
            # anchor = "center",
        ).place(
            relx = 0.475, rely = 0.425, anchor = 'e',
        )
        
        # Button Computer Device
        button_lab_cd = ctk.CTkButton(
            self,
            fg_color = 'black',
            text = 'Computer\n\nDevice',
            font = ("Kemco Pixel", 20),
            text_color = "#F7AC13",
            hover_color = '#4E4500', #7A6D00
            border_color = '#F7AC13',
            border_width = 3,
            width = 150,
            height = 150,
            corner_radius = 0,
            # command = lambda : self.master.switch_frame(ManualFrame)
            # anchor = "center",
        ).place(
            relx = 0.525, rely = 0.425, anchor = 'w',
        )
        
        # Button Embedded System
        button_lab_emsy = ctk.CTkButton(
            self,
            fg_color = 'black',
            text = 'Embedded\n\nSystem',
            font = ("Kemco Pixel", 20),
            text_color = "#F7AC13",
            hover_color = '#4E4500', #7A6D00
            border_color = '#F7AC13',
            border_width = 3,
            width = 150,
            height = 150,
            corner_radius = 0,
            # command = lambda : self.master.switch_frame(ManualFrame)
            # anchor = "center",
        ).place(
            relx = 0.775, rely = 0.425, anchor = 'w',
        )
        
        # Button Kendali Lab
        button_lab_programming = ctk.CTkButton(
            self,
            fg_color = 'black',
            text = 'Lab\n\nKendali',
            font = ("Kemco Pixel", 20),
            text_color = "#F7AC13",
            hover_color = '#4E4500', #7A6D00
            border_color = '#F7AC13',
            border_width = 3,
            width = 150,
            height = 150,
            corner_radius = 0,
            # command = lambda : self.master.switch_frame(ManualFrame)
            # anchor = "center",
        ).place(
            relx = 0.225, rely = 0.8, anchor = 'e',
        )
        
        # Button PLC Lab
        button_lab_sensorik = ctk.CTkButton(
            self,
            fg_color = 'black',
            text = 'Lab\n\nPLC',
            font = ("Kemco Pixel", 20),
            text_color = "#F7AC13",
            hover_color = '#4E4500', #7A6D00
            border_color = '#F7AC13',
            border_width = 3,
            width = 150,
            height = 150,
            corner_radius = 0,
            # command = lambda : self.master.switch_frame(ManualFrame)
            # anchor = "center",
        ).place(
            relx = 0.475, rely = 0.8, anchor = 'e',
        )
        
        # Button Pneumatic Hidraulics
        button_lab_cd = ctk.CTkButton(
            self,
            fg_color = 'black',
            text = 'Pneumatic\n\nHidraulic',
            font = ("Kemco Pixel", 18),
            text_color = "#F7AC13",
            hover_color = '#4E4500', #7A6D00
            border_color = '#F7AC13',
            border_width = 3,
            width = 150,
            height = 150,
            corner_radius = 0,
            # command = lambda : self.master.switch_frame(ManualFrame)
            # anchor = "center",
        ).place(
            relx = 0.525, rely = 0.8, anchor = 'w',
        )
        
        # Button Classroom A3
        button_lab_emsy = ctk.CTkButton(
            self,
            fg_color = 'black',
            text = 'A3\n\nClassroom',
            font = ("Kemco Pixel", 18),
            text_color = "#F7AC13",
            hover_color = '#4E4500', #7A6D00
            border_color = '#F7AC13',
            border_width = 3,
            width = 150,
            height = 150,
            corner_radius = 0,
            # command = lambda : self.master.switch_frame(ManualFrame)
            # anchor = "center",
        ).place(
            relx = 0.775, rely = 0.8, anchor = 'w',
        )
        
        
        # # Button Programming Lab
        # image_lab_programming = ctk.CTkImage(light_image = Image.open(
        #     '/home/bintangpascallo/GUI_robot/Assets/images/ButtonLabProgramming.png'
        #     ),size = (150, 150))
        
        # button_lab_programming = ctk.CTkButton(
        #     self,
        #     fg_color = 'black',
        #     image = image_lab_programming,
        #     text = '',
        #     hover_color = '#4E4500', #7A6D00
        #     # command = lambda : self.master.switch_frame(ManualFrame)
        #     # anchor = "center",
        # )
        
        # button_lab_programming.place(
        #     relx = 0.125, rely = 0.425, anchor = 'center',
        # )
        
        # # Button Lab Sensorik
        # image_lab_sensorik = ctk.CTkImage(light_image = Image.open(
        #     '/home/bintangpascallo/GUI_robot/Assets/images/ButtonLabSensorik.png'
        #     ),size = (150, 150))
        
        # button_lab_sensorik = ctk.CTkButton(
        #     self,
        #     fg_color = 'black',
        #     image = image_lab_sensorik,
        #     text = '',
        #     hover_color = '#4E4500', #7A6D00
        #     # command = lambda : self.master.switch_frame(ManualFrame)
        #     # anchor = "center",
        # )
        
        # button_lab_sensorik.place(
        #     relx = 0.325, rely = 0.425, anchor = 'center',
        # )
        
        # # button_lab_sensorik.pack(
        # #     anchor = 'w',  
        # #     padx = 100,  
        # #     pady = 60,  
        # #     # ipadx = 10
        # #     # relx = 0.325, rely = 0.425, anchor = 'center',
        # # )
        
        # # Button Computer Device
        # image_computer_device = ctk.CTkImage(light_image = Image.open(
        #     '/home/bintangpascallo/GUI_robot/Assets/images/ButtonComputerDevice.png'
        #     ),size = (150, 150))
        
        # button_computer_device = ctk.CTkButton(
        #     self,
        #     fg_color = 'black',
        #     image = image_computer_device,
        #     text = '',
        #     hover_color = '#4E4500', #7A6D00
        #     # command = lambda : self.master.switch_frame(ManualFrame)
        #     # anchor = "center",
        # )
        
        # button_computer_device.place(
        #     relx = 0.625, rely = 0.425, anchor = 'center',
        # )
        
        # # Button Embedded System
        # image_embedded_system = ctk.CTkImage(light_image = Image.open(
        #     '/home/bintangpascallo/GUI_robot/Assets/images/ButtonEmbeddedSystem.png'
        #     ),size = (150, 150))
        
        # button_embedded_system = ctk.CTkButton(
        #     self,
        #     fg_color = 'black',
        #     image = image_embedded_system,
        #     text = '',
        #     hover_color = '#4E4500', #7A6D00
        #     # command = lambda : self.master.switch_frame(ManualFrame)
        #     # anchor = "center",
        # )
        
        # button_embedded_system.place(
        #     relx = 0.825, rely = 0.425, anchor = 'center',
        # )
        
        # # Button Programming Lab
        # image_lab_programming = ctk.CTkImage(light_image = Image.open(
        #     '/home/bintangpascallo/GUI_robot/Assets/images/ButtonLabProgramming.png'
        #     ),size = (150, 150))
        
        # button_lab_programming = ctk.CTkButton(
        #     self,
        #     fg_color = 'black',
        #     image = image_lab_programming,
        #     text = '',
        #     hover_color = '#4E4500', #7A6D00
        #     # command = lambda : self.master.switch_frame(ManualFrame)
        #     # anchor = "center",
        # )
        
        # button_lab_programming.place(
        #     relx = 0.125, rely = 0.8, anchor = 'center',
        # )
        
        # # Button Lab Sensorik
        # image_lab_sensorik = ctk.CTkImage(light_image = Image.open(
        #     '/home/bintangpascallo/GUI_robot/Assets/images/ButtonLabSensorik.png'
        #     ),size = (150, 150))
        
        # button_lab_sensorik = ctk.CTkButton(
        #     self,
        #     fg_color = 'black',
        #     image = image_lab_sensorik,
        #     text = '',
        #     hover_color = '#4E4500', #7A6D00
        #     # command = lambda : self.master.switch_frame(ManualFrame)
        #     # anchor = "center",
        # )
        
        # button_lab_sensorik.place(
        #     relx = 0.325, rely = 0.8, anchor = 'center',
        # )
        
        # # Button Computer Device
        # image_computer_device = ctk.CTkImage(light_image = Image.open(
        #     '/home/bintangpascallo/GUI_robot/Assets/images/ButtonComputerDevice.png'
        #     ),size = (150, 150))
        
        # button_computer_device = ctk.CTkButton(
        #     self,
        #     fg_color = 'black',
        #     image = image_computer_device,
        #     text = '',
        #     hover_color = '#4E4500', #7A6D00
        #     # command = lambda : self.master.switch_frame(ManualFrame)
        #     # anchor = "center",
        # )
        
        # button_computer_device.place(
        #     relx = 0.625, rely = 0.8, anchor = 'center',
        # )
        
        # # Button Embedded System
        # image_embedded_system = ctk.CTkImage(light_image = Image.open(
        #     '/home/bintangpascallo/GUI_robot/Assets/images/ButtonEmbeddedSystem.png'
        #     ),size = (150, 150))
        
        # button_embedded_system = ctk.CTkButton(
        #     self,
        #     fg_color = 'black',
        #     image = image_embedded_system,
        #     text = '',
        #     hover_color = '#4E4500', #7A6D00
        #     # command = lambda : self.master.switch_frame(ManualFrame)
        #     # anchor = "center",
        # )
        
        # button_embedded_system.place(
        #     relx = 0.825, rely = 0.8, anchor = 'center',
        # )
        
        self._frame = None
    
    # Swicth Frame Logic
    def switch_frame(self, frame_class):
        # Declare New Frame
        new_frame = frame_class(self)
        
        # Destroy The Frame
        if self._frame is not None:
            self._frame.destroy()
            
        self._frame = new_frame
        self._frame.pack(expand = True, fill = "both")  
    
# Manual Class
class ManualFrame(ctk.CTkFrame):
    def __init__(self,  master, **kwargs):
        super().__init__(master, **kwargs)
        
        # Frame Configuration
        self.configure(fg_color = 'black')
        
        # Create Title
        title_manual = ctk.CTkLabel(
            self,
            text = 'Manual Mode',
            font = ("Kemco Pixel", 50),
            text_color = "#F7AC13"
        )
        
        title_manual.place(relx = 0.5, rely = 0.1, anchor = 'center')
        
        # Create Message
        title_joystick = ctk.CTkLabel(
            self,
            text = 'Connect The Joystick',
            font = ("Kemco Pixel", 35),
            text_color = "#F7AC13"
        )
        
        title_joystick.place(relx = 0.5, rely = 0.4, anchor = 'center')
        
        title_connect_status = ctk.CTkLabel(
            self,
            text = 'Not Connected',
            font = ("Kemco Pixel", 35),
            text_color = "#F7AC13"
        )
        
        title_connect_status.place(relx = 0.5, rely = 0.6, anchor = 'center')
        
        # Create Back Button Configuration
        image_exit = ctk.CTkImage(light_image = Image.open(
            '/home/bintangpascallo/GUI_robot/Assets/images/ButtonBack.png'
            ),size = (45, 45))
        
        button_back = ctk.CTkButton(
            self,
            fg_color = 'black',
            image = image_exit,
            text = '',
            width = 45,
            height = 45,
            hover_color = '#4E4500', #7A6D00
            command = lambda : self.switch_frame(AutoManualFrame) # self.back() 
            # anchor = "center",
        )
        
        button_back.place(
            relx = 0.075, rely = 0.1, anchor = 'center',
        )
        
        self._frame = None
    
    # Swicth Frame Logic
    def switch_frame(self, frame_class):
        # Declare New Frame
        new_frame = frame_class(self)
        
        # Destroy The Frame
        if self._frame is not None:
            self._frame.destroy()
            
        self._frame = new_frame
        self._frame.pack(expand = True, fill = "both")  
        
        
# Main Program Run
if __name__ == "__main__":
    main = MainApp() 
    main.mainloop()

