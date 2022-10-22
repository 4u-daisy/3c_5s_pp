import numpy as np

def read_file(path:str):

    file_matrix_a = open(path, 'r')

    rows, columns = file_matrix_a.readline().split(' ')
    _rows, _columns = int(rows), int(columns)

    a = []
    for i in range(_rows):
        a.append([0] * (_columns))

    for i in range(_rows):
        s = file_matrix_a.readline().split(' ')
        for j in range(_columns):
            a[i][j] = int(s[j])
    file_matrix_a.close()
    return a

def mull_matrix(a, b):
    return np.dot(a, b)

def match_test(data, result) -> bool:
    rows, columns = len(data), len(data[0])
    _rows, _columns = len(result), len(result[0])

    if (rows != _rows or columns != columns):
        return False

    for i in range(rows):
        for j in range(columns):
            if (data[i][j] != result[i][j]):
                return False

    return True


#file_matrix_a = open('C:\\Users\\HOME\\source\\repos\\PP\\PP\\a.txt', 'r')
#file_matrix_b = open('C:\\Users\\HOME\\source\\repos\\PP\\PP\\b.txt', 'r')
#file_matrix_c = open('C:\\Users\\HOME\\source\\repos\\PP\\PP\\c.txt', 'r')

a = read_file('C:\\Users\\HOME\\source\\repos\\PP\\PP\\a.txt')
b = read_file('C:\\Users\\HOME\\source\\repos\\PP\\PP\\b.txt')
c = read_file('C:\\Users\\HOME\\source\\repos\\PP\\PP\\c.txt')

test_c = mull_matrix(a, b)

print(match_test(c, test_c))







