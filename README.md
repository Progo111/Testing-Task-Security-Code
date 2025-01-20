# Testing-Task-Security-Code
## Сборка проекта

```
mkdir build
cd build
cmake -G "Visual Studio 17 2022" -A <arch>
cmake --build . --config Release

```

arch может быть либо Win32, либо x64.

## Запуск программы из папки build

`.\Release\DiskInfoUtility.exe <arguments>`

Аргументы которые принимает программа:
- "--targe <number>" обязательный аргумент, отвечает за номер задачи. number может быть от 1 до 3.
    1. Перечисление локальных дисков (логических томов) рабочей станции, на которой приложение выполняется. Для каждого тома следует указать следующую информацию:
    * Имя тома
    * Размер тома в байтах
    * Имя файловой системы тома (строковое обозначение типа файловой системы)
    2. Перечисления всех файлов и папок, располагаемых на каждом из логических томов (т.е. все файловые объекты тома, а не только те, которые расположены в его корне). С указанием их параметров:
    * Имя файла/папки
    * Временная метка создания данного объекта в формате YYYY-MM-DD hh-mm
    * Тип объекта (папка/файл)
    * Общее число файлов
    * Общее число папок
    3. Сбор информации:
    * Полное имя пользователя, запустившего приложение
    * Список групп, в которые входит пользователь
    * Имя рабочей станции
- "--log" необязательный аргумент, отвечает за включение отладочной информации. По умолчанию отладочная информация выключена.
- "-o <filename>" необязательный аргумент, отвечает за файл вывода информации в кодировке UTF-8. По умолчанию "output.txt"
