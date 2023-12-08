import random

def generate_hex_numbers(n):
    hex_numbers = [hex(random.randint(0, 1.7014118e+38))[2:].zfill(2) for _ in range(n)]
    return hex_numbers

def write_to_file(filename, data):
    with open(filename, 'w') as file:
        for item in data:
            file.write(f"{item}\n")

# Пример использования: генерация 5 случайных шестнадцатеричных чисел и запись в файл
n = 1000000
hex_numbers = generate_hex_numbers(n)

filename = '/home/kirill/Desktop/study/zaika/MAI_OS/lab2/input_files/input.txt'
write_to_file(filename, hex_numbers)

print(f"Сгенерированные числа сохранены в файл {filename}.")