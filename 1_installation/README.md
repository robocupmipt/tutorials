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

 # 4) Install: SDK and cross-toolchain

Необходимо скачать и разархиваровать [SDK для С++](https://drive.google.com/open?id=1vSsmdZ-FWL_bBMNC06_iaHsDi77jvbwS) и [cross-toolchain](https://drive.google.com/open?id=162PeZSlJ2_Skj8nzoH5qBYcyolB-7E3t) для компиляции кода для запуска на роботе.

# 5) Configuration: qiBuild Toolchains

Создадим toolchain для компиляции под `ubuntu` с именем "linux-sdk", указав вместо "path_to_SDK" путь до разархивированной папки "naoqi-sdk-2.8.2.15-linux64":
 
    -> qitoolchain create linux-sdk path_to_SDK/toolchain.xml
  
Далее добавим конфигурацию в qibuild:
  
    -> qibuild add-config linux-sdk -t linux-sdk
  
Для того, чтобы запускать код на роботе, необходимо компилировать его с помощью специального cross-toolchain (более подробная информация [тут](http://doc.aldebaran.com/qibuild/beginner/qibuild/aldebaran.html#qibuild-using-aldebaran-packages)).

Создадим toolchainс именем "atom-sdk" под `робота`, указав вместо "path_to_cross-toolchain" путь до разархивированной папки "ctc-linux64-atom-2.8.2.15":
  
    -> qitoolchain create atom-sdk path_to_cross-toolchain/toolchain.xml
  
Далее добавим конфигурацию в qibuild:
  
    -> qibuild add-config atom-sdk -t atom-sdk    
    
Более подробная информация о фреймворке qibuild [здесь](http://doc.aldebaran.com/qibuild/hacking/design/cmake/index.html#term-feed)

# NOTE: 

Если вы удалите или переместите папку с SDK или cross-toolchain'oм, вам придётся заново его конфигурировать. Для этого нужно предварительно удалить информацию о предыдущей конфигурации:

    -> qitoolchain remove --force name_of_toolchain
    
Список сконфигурированных toolchain'ов можно посмотреть командой:

    -> qitoolchain list

 # 6) Compile the Program C++ with the SDK - ALDEBARAN

Создайте новый проект, если это необходимо:

    -> qisrc create template

(или же перейдите в директорию одного из примеров)

Иницируйте рабочее дерево:

    -> qibuild init
    
Далее необходимо сконфигурировать qibuild для использования одного из toolchain и собрать код с помощью него (вместе toolchain нужно указать имя toolchain'а, который вы намереваетесь использовать):
    
    -> qibuild configure -c toolchain
    
    -> qibuild make -c toolchain
    
 # 7) Start the Project 
 
 В дальнейших пунктах нашего мануала будет подробно рассказано о том, как запускать код и удалённо на своём компьютере, и непосредственно на роботе. Пока же рекомендуется прочитать, [как подключаться к роботу](https://github.com/robocupmipt/tutorials/blob/master/1_installation/connection-to-the-robot.md).
