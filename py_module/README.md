# Создание модуля на Python

Лучше сначала прочитать туториал по созданию модуля на C++, ибо идейно они не отличаются. 

Чтобы добавить модуль в систему робота, добавьте в файл `/home/nao/naoqi/preferences/autoload.ini` на роботе строчки:

        -> [user]
    
        -> /path/to/python_module.py

Кратно пробежимся по содержимому файла. 

- Класс HumanGreeter, наследованный от ALModule - реализует всю идею модуля. 
- функция main() привязывает модуль к брокеру.

В классе HumanGreeter присутствует метод onFaceDetected(). Это обработчик события, который срабатывает в случае, когда перед роботом появляется человек. 

Чтобы не принимать, а наоброт генерировать исключения нужны следующие строчки:

```
from naoqi import ALProxy

# create proxy on ALMemory
memProxy = ALProxy("ALMemory","localhost",9559)

#raise event. Data can be int, float, list, string
memProxy.raiseEvent("My event", "data")
```
