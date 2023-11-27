# Лабораторная работа №1

#### Вариант 21

## Цель работы:
##### Приобретение практических навыков в:

- Управление процессами в ОС
- Обеспечение обмена данных между процессами посредством каналов

## Задание:

```
Составить и отладить программу на языке Си, осуществляющую работу с процессами и
взаимодействие между ними в одной из двух операционных систем. В результате работы
программа (основной процесс) должен создать для решение задачи один или несколько
дочерних процессов. Взаимодействие между процессами осуществляется через системные
сигналы/события и/или каналы (pipe).
Необходимо обрабатывать системные ошибки, которые могут возникнуть в результате работы.
```

### Задание варианта:
![](https://i.imgur.com/80tR3o3.png)

```
Родительский процесс создает два дочерних процесса. Первой строкой пользователь в консоль
родительского процесса вводит имя файла, которое будет использовано для открытия File с таким
именем на запись для child1. Аналогично для второй строки и процесса child2. Родительский и
дочерний процесс должны быть представлены разными программами.

Родительский процесс принимает от пользователя строки произвольной длины и пересылает их в
pipe1 или в pipe2 в зависимости от правила фильтрации. Процесс child1 и child2 производят работу
над строками. Процессы пишут результаты своей работы в стандартный вывод.

Правило фильтрации: нечетные строки отправляются в pipe1, четные в pipe2. Дочерние процессы инвертируют строки.
```


### Команды для запуска:
Build project:
```
make build
```

Run program:
```
make run
```

Check strace:
```
make strace
```