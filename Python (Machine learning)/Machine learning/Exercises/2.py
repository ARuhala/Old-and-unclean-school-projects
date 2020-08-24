import pickle
import numpy as np
from pathlib import Path
from random import randint
from sys import maxsize
'''
Loaded in this way, each of the batch files contains a dictionary with the following elements:
data -- a 10000x3072 numpy array of uint8s.
Each row of the array stores a 32x32 colour image.
The first 1024 entries contain the red channel values, the next 1024 the green, and the final 1024 the blue.
The image is stored in row-major order, so that the first 32 entries of the array are the red channel values of the first row of the image.
labels -- a list of 10000 numbers in the range 0-9. The number at index i indicates the label of the ith image in the array data.
'''
def unpickle(file):
    with open(file, 'rb') as fo:
        dict = pickle.load(fo, encoding='bytes')
    return dict

# copying from the matlab conf file
cifar10_dir = Path("C:/Users/VStore/Desktop/Koulu/MachineLearning/cifar-10-python.tar/cifar-10-batches-py")
train_files = ['data_batch_1',
                'data_batch_2',
                'data_batch_3',
                'data_batch_4',
                'data_batch_5']
test_file = 'test_batch'
meta_file = 'batches.meta'

# Read training data and form the feature matrix and target output
tr_data = np.array([])
tr_labels = []
file_as_dict = {}
print('Reading training data...\n')
for train_file_ind in range(len(train_files)):
  print('\r  Reading', train_files[train_file_ind])
  file_as_dict = unpickle(str(cifar10_dir / train_files[train_file_ind]))
  if train_file_ind == 0:
      tr_data = file_as_dict[b'data']
  else:
      tr_data = np.concatenate((tr_data, file_as_dict[b'data']), axis=0)
  tr_labels.extend(file_as_dict[b'labels'])

print('Done!\n')
'''
data -- a 10000x3072 numpy array of uint8s.
Each row of the array stores a 32x32 colour image.
The first 1024 entries contain the red channel values,
 the next 1024 the green,
  and the final 1024 the blue.
The image is stored in row-major order, so that the first 32 entries of the array are the red channel values of the first row of the image.
'''

print("training data dimensions: ", tr_data.shape)
print("training labels list's length: ", len(tr_labels))


def cifar_10_evaluate(pred,gt):
    '''
    :param pred: predicted labels (gueeses)
    :param gt: true labels, groundtruth
    :return: number between 0.0 - 1.0
    '''

    pred_len = len(pred)
    gt_len = len(gt)

    # check that pred and gt are the same length before starting the long calculations
    if (pred_len != gt_len or pred_len == 0 or gt_len == 0):
        print("mismatch of label list lengths or lengths were 0")
        return 0

    right_labels = 0
    for label_index in range(pred_len):
        if pred[label_index] == gt[label_index]:
            right_labels = right_labels +1

    return (right_labels / gt_len)

def cifar_10_rand(x):
    '''
    :param x: test samples, 50 000 , 3072 dimensional numpy array
    :return: 50 000 numbers between 1 and 10
    '''

    number_of_rows = x.shape[0]
    print("Generating", number_of_rows, "random labels")
    random_label_list = []
    for row_index in range(number_of_rows):
        random_label_list.append(randint(0,9))
    print("Done generating", len(random_label_list), "random labels")
    return random_label_list


'''
Reading the test data similarly to the training data
'''
print("Reading test data")


test_file_as_dict = unpickle(str(cifar10_dir / test_file))
te_data = test_file_as_dict[b'data']
te_labels = []
te_labels.extend(test_file_as_dict[b'labels'])
print("test data dimensions: ", te_data.shape)
print("test labels list's length: ", len(te_labels))
print('Done!\n')

def cifar_10_1NN(x,trdata,trlabels):
    '''
Write a function cifar 10 1NN(x,trdata,trlabels) that finds the best match of the input vector x in the
training set trdata and returns the same label. Make a script that inputs all CIFAR-10 test samples to
this function and evaluate its classification accuracy using your evaluation function.
Make sure your 1NN function works by testing with the training data itself (should provide perfect
accuracy).

x input data as a numpy array
trdata training data as a numpy array
trlabels training labels as a list
    '''

    print("Starting nearest neighbour calculations")
    label_guess_list = []
    # limit the dev phase to the first 1000 rows

    x = x.astype(float)
    trdata = trdata.astype(float)

    #trdatasize = np.size(10000)

    for x_index in range (1000):
        closest_row = 0
        closest_row_distance = maxsize
        closest_row_label = 0
        for row_index in range(1000):
            # compare first row of x to all rows of trdata
            compareable_distance = np.linalg.norm(x[x_index] - trdata[row_index])
            if (compareable_distance < closest_row_distance):
                closest_row_distance = compareable_distance
                # select/update closest row of trdata
                # take closest rows corresponding label from the trlabels[index] as the closest row is trdata[index]
                closest_row = row_index
                closest_row_label = trlabels[row_index]
        # add the guess into the guess list
        print("Calculations for row", x_index, "finished with closest row:", closest_row, "Closest row distance:", closest_row_distance, "Closest row label:", closest_row_label)
        label_guess_list.append(closest_row_label)


    # input label guess list into the evaluation
    # input trlabels of same length into the evaluation
    evaluation = cifar_10_evaluate(label_guess_list, te_labels[:len(label_guess_list)])
    print("Evaluation score: ", evaluation)


def main():
    # FOR TESTING THE FIRST EXERCISES
    # random_labels = cifar_10_rand(tr_data)
    # evaluation = cifar_10_evaluate(random_labels,tr_labels)
    # print("Evaluation score: ", evaluation)

    cifar_10_1NN(te_data,tr_data,tr_labels)

main()