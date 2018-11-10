# Создание локального модуля

### Описание файлов
- `mymodule.h` и `mymodule.cpp` - непосредсвенно класс, выполняющий всю логику модуля. 
- `main.cpp` Этот файл нужен для того, чтобы присоединить нам модуль к системе робота. 
- `CMakeLists.txt` и `qiproject.xml` - файлы, нужные для компиляции с помощью `qibuild`.

Более детально: если скомпилировать наш модуль, то на выходе получим файл с расширением .so, который можно динамически прилинковать к системе робота. При этом нужно использовать toolchain для робота. 

### Как собрать проект

Можно сделать `git clone` и в этой же папке выполнить:

    -> qibuild configure -c toolchain_for_robot
    -> qibuild make -c toolchain_for_robot

### Как динамически прилинковать библиотеку

* Добавить файл с расширением .so, который создался в папке /build-.../sdk/lib/naoqi в результате сборки, в `/home/nao/some_directory` на роботе (о том, как это сделать, можно ещё раз прочитать [здесь](https://github.com/robocupmipt/tutorials/blob/master/1_installation/connection-to-the-robot.md)). 
* В файле `/home/nao/naoqi/preferences/autoload.ini` на роботе добавить строчку:

    -> [user]
    -> /path/to/libmymodule.so