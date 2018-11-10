# Установка SDK и cross-toolchain

# 1) The pre-requisites:

    -> sudo apt-get install build-essential checkinstall 

    -> sudo apt-get install gcc-multilib libreadline-gplv2-dev libncursesw5-dev libssl-dev libsqlite3-dev tk-dev libgdbm-dev libc6-dev libc6-i386 libbz2-dev 

# 2) Install: Python 2.7 (only) + CMake + QTCreator 

    -> sudo apt-get install gcc cmake qtcreator 

    -> cd /usr/src 

    -> wget https://www.python.org/ftp/python/2.7.13/Python-2.7.13.tgz 

    -> tar xzf Python-2.7.13.tgz 

    -> cd Python-2.7.13 

    -> sudo ./configure 

    -> sudo make altinstall 

# 3) Install: qiBuild 

    -> sudo apt install python-pip

    -> pip install qibuild

  If qiBuild doesn't launch: 

        -> gedit ~/.bashrc and in the end of the file add: export PATH=${PATH}:${HOME}/.local/bin

 # 4) Install SDK and cross-toolchain

    -> git clone https://github.com/MolVlad/Robocup2019
    
You should create a new branch with your last name:
    
    -> git checkout -b <last_name>
    
Then you should write me your login in GitHub, so that I add you to the list of collaborators (link to my page: vk.com/molvlad)

After that you will be able make changes and save them on your branch:

    -> git add <names_of_modified_files>
    
    -> git commit -m "<message for the other people"
    
    -> git push origin <name_of_branch>
    
Note: you should work only in your branch!

Download and unzip to the directory Robocup2019:
    
    https://drive.google.com/open?id=162PeZSlJ2_Skj8nzoH5qBYcyolB-7E3t

# 5) Configuration: qiBuild Toolchains

 You can just execute my script:
 
    -> ./config_toolchain
    
 or configure manually:

 Configure toolchain for the desktop:
 
    -> qitoolchain create desktop Robocup2019/naoqi/toolchain.xml
  
    -> qibuild add-config desktop -t desktop
  
  Configure toolchain for the robot:
  
    -> qitoolchain create robot /toolchain.xml
  
    -> qibuild add-config robot -t robot                                       

 # 6) Compile the Program C++ with the SDK - ALDEBARAN

Create a new project (if it's necessary, or move to the directory with example):

    -> qisrc create template

Then init worktree:

    -> qibuild init
    
 Below <toolchain> means "toolchain_for_desktop", if you want to build for the desktop, or "toolchain_for_robot" otherwise:
    
    -> qibuild configure -c <toolchain>
    
    -> qibuild make -c <toolchain>
    
 # 7) Start the Project 
 
 If you build your project for the desktop:
 
    -> cd build-toolchain_for_the_robot/sdk/bin
    
 Below <example> is the name of your program, <IP_address> - IP address of the robot.
    
    -> ./<example> <IP_address>
    
 If you build your project for the robot:
 
     -> cd build-toolchain_for_the_robot/sdk/bin
     
    -> scp <example> nao@<IP_address>:/home/nao/<your_directory>
    
    -> ssh nao@<IP_address>
    
    -> ./<your_directory>/<example> <IP_address>
    
 To work with the robot you should create on him a new directory with your last name and copy files there. Otherwise everything will be remove.
    
# Note:

If you want to create a local module, at the end of building you will get a static library .so, that cannot be run as an ordinary program.
