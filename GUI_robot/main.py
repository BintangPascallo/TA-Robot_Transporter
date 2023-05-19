# Libraries
import customtkinter as ctk
import os
from PIL import ImageTk,Image  
import signal
import tkinter as tk
import socket
from time import sleep

# Call Class
# from font_style import *
# from splashscreen import *
# from menu import *

# Declare Global
ip_val = " Check IP Address"

# Main Class
class MainApp(ctk.CTk):
    def __init__(self):
        super().__init__()
        
        # Configuration
        self.wm_attributes('-type','splash')
        self.attributes('-topmost', True)
        self.after_idle(self.attributes,'-topmost',False)
        self.resizable(False, False)
        self.configure(bg='black')
        self.title('Robot Transporter')
        # self.overrideredirect(False) # or 1 instead of True
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
        self.after(1000, lambda : self.switch_frame(MainMenuFrame)) 
        
    # Swith Frame Logic
    def switch_frame(self, frame_class):
        # Declare New Frame
        new_frame = frame_class(self)
        
        # Destroy The Frame
        if self._frame is not None:
            self._frame.destroy()
            
        self._frame = new_frame
        self._frame.pack(expand = True, fill = "both")
        
        
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
        
        button_exit = ctk.CTkButton(
            self,
            fg_color = 'black',
            image = image_exit,
            text = '',
            width = 45,
            height = 45,
            hover_color = '#4E4500', #7A6D00
            command = lambda : exit_apps()
            # exit()
            # anchor = "center",
        )
        
        button_exit.place(
            relx = 0.075, rely = 0.1, anchor = 'center',
        )
        
        # Exit Program
        def exit_apps():
            exit_apps = tk.messagebox.askquestion('Warning', 'Do you want to close this application?')
            if exit_apps == 'yes':
                tk.messagebox.showwarning('Warning', 'Turning Off the Robot Operating System in 5 Seconds')
                os.system("gnome-terminal -e 'bash -c \"rosnode kill -a; killall -9 rosmaster; killall -9 roscore exit; sleep 4; exit; exec bash\"'")
                sleep(5)
                exit()
            elif exit_apps == 'no':
                tk.messagebox.showinfo('Warning', 'This application is not closed!')
            else:
                tk.messagebox.showwarning('Error', 'Something went wrong!')
        
        # Create Launch Button Configuration
        image_launch = ctk.CTkImage(light_image = Image.open(
            '/home/bintangpascallo/GUI_robot/Assets/images/ButtonLaunch.png'
            ),size = (215, 280))
        
        button_launch = ctk.CTkButton(
            self,
            fg_color = 'black',
            image = image_launch,
            text = '',
            hover_color = '#4E4500', #7A6D00
            command = lambda : master.switch_frame(AutoManualFrame)
            # anchor = "center",
        )
        
        button_launch.place(
            relx = 0.19, rely = 0.575, anchor = 'center',
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
            hover_color = '#4E4500', #7A6D00
            command = lambda : master.switch_frame(SettingFrame)
            # anchor = "center",
        )
        
        button_setting.place(
            relx = 0.5, rely = 0.575, anchor = 'center',
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
            hover_color = '#4E4500', #7A6D00
            # command = lambda : Roscore()
            # anchor = "center",
        )
        
        button_help.place(
            relx = 0.81, rely = 0.575, anchor = 'center',
        )
        
#CTkScrollableFrame(app, width=200, height=200)
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
        
        # IP Address Checker
        hostname = socket.gethostname()
        IPAddr = socket.gethostbyname(hostname)
        ip_address = str(IPAddr)
        global ip_val
        ip_val = ' Check IP Address : ' + ip_address
        
        button_ipcheck = ctk.CTkButton(
            self,
            fg_color = 'black',
            text = ip_val,
            font = ("Kemco Pixel", 20),
            text_color = "#F7AC13",
            hover_color = '#4E4500', #7A6D00
            border_color = '#F7AC13',
            border_width = 3,
            width = 700,
            height = 50,
            corner_radius = 0,
            command = lambda : ip_checker(),
            anchor = "w",
        )
        
        button_ipcheck.place(
            relx = 0.065, rely = 0.3
        )
        
        # IP Checker Program
        def ip_checker():
            hostname = socket.gethostname()
            IPAddr = socket.gethostbyname(hostname)
            ip_address = str(IPAddr)
            
            global ip_val
            ip_val = ' Check IP Address : ' + ip_address
            self.switch_frame(SettingFrame)
        
        # Edit IP Address for ROS open .bashrc
        button_edit_ros_ip = ctk.CTkButton(
            self,
            fg_color = 'black',
            text = ' Edit ROS IP Address',
            font = ("Kemco Pixel", 20),
            text_color = "#F7AC13",
            hover_color = '#4E4500', #7A6D00
            border_color = '#F7AC13',
            border_width = 3,
            width = 700,
            height = 50,
            corner_radius = 0,
            command = lambda : ip_editor(),
            anchor = "w",
        )
        
        button_edit_ros_ip.place(
            relx = 0.065, rely = 0.45
        )
        
        # IP Editor Program
        def ip_editor():
            os.popen('sh /home/bintangpascallo/ipconfig.sh')
            # os.system("gnome-terminal -e 'bash -c \"source ~/.bashrc; gedit ~/.bashrc; exit; exec bash\"'")
        
        # Activate LIDAR
        button_lidar = ctk.CTkButton(
            self,
            fg_color = 'black',
            text = ' Activate Lidar Sensor',
            font = ("Kemco Pixel", 20),
            text_color = "#F7AC13",
            hover_color = '#4E4500', #7A6D00
            border_color = '#F7AC13',
            border_width = 3,
            width = 700,
            height = 50,
            corner_radius = 0,
            command = lambda : lidar_sens_on(),
            anchor = "w",
        )
        
        button_lidar.place(
            relx = 0.065, rely = 0.6
        )
        
        # LIDAR On
        def lidar_sens_on():
            os.system("gnome-terminal -e 'bash -c \"cd; source /home/bintangpascallo/catkin_ws/devel/setup.bash; roslaunch ydlidar lidar.launch; exit; exec bash\"'")
        
        # Activate Ros Serial
        button_lidar = ctk.CTkButton(
            self,
            fg_color = 'black',
            text = ' Activate ROS Serial',
            font = ("Kemco Pixel", 20),
            text_color = "#F7AC13",
            hover_color = '#4E4500', #7A6D00
            border_color = '#F7AC13',
            border_width = 3,
            width = 700,
            height = 50,
            corner_radius = 0,
            command = lambda : rosserial(),
            anchor = "w",
        )
        
        button_lidar.place(
            relx = 0.065, rely = 0.75
        )
        
        # ROSSERIAL ON
        def rosserial():
            os.system("gnome-terminal -e 'bash -c \"cd; rosrun teleop_twist_keyboard teleop_twist_keyboard.py; exit; exec bash\"'")
        
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
        title_connect = ctk.CTkLabel(
            self,
            text = 'Connect With Phone or\n\nROS Teleoperation',
            font = ("Kemco Pixel", 30),
            text_color = "#F7AC13"
        )
        
        title_connect.place(relx = 0.5, rely = 0.4, anchor = 'center')
        
        # IP Address Checker
        hostname = socket.gethostname()
        IPAddr = socket.gethostbyname(hostname)
        ip_address = str(IPAddr)
        global ip_val
        ip_val = ' IP Address : ' + ip_address
        
        title_connect_status = ctk.CTkLabel(
            self,
            text = ip_val,
            font = ("Kemco Pixel", 35),
            text_color = "#F7AC13"
        )
        
        title_connect_status.place(relx = 0.5, rely = 0.7, anchor = 'center')
        
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
