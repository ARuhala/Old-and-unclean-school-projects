# exercise 1
import numpy as np
import matplotlib.pyplot as plt
plt.style.use('seaborn-whitegrid')

# a
def sigma_sum(parameter_list):
    result = 0
    for element in parameter_list:
        result += element
    return result


def a_solve (x, y):
    # x and y are numpy arrays
    # a = ( np.sum(x) * np.sum(y) - np.sum(x * y) ) / (np.sum(np.square(x)) - np.sum(x)**2)
    a = (np.sum(x * y ) - ( np.sum(y) * np.sum(x) / len(x) )) / (np.sum(np.square(x)) - (np.sum(x)**2) / len(x))
    return a

def b_solve (x,y,):
    # x and y are numpy arrays
    b = ( np.sum(y) - a_solve(x,y)*np.sum(x) ) / len(x)
    return b


# b
def linfit (x,y):
    # takes x,y returns a and b
    return a_solve(x,y), b_solve(x,y)


# c
# plot the points and the line


def main():
    x_list = np.array([])
    y_list = np.array([])





    # drawing with matplotlib.pyplot
    fig = plt.figure()
    ax = plt.axes()
    xy_tuple = plt.ginput(10, show_clicks = True)

    for element in xy_tuple:
        print(element)
        x_list = np.append(x_list,element[0])
        y_list = np.append(y_list,element[1])
    print(x_list)
    print(y_list)
    a,b = linfit(x_list, y_list)
    print("a =", a,"b =", b)
    # plotting the line
    ax.plot(x_list, a*x_list+b)
    # plotting the points
    ax.plot(x_list, y_list, 'x')
    print(xy_tuple)
    plt.show()

main()