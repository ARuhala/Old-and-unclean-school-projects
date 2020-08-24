import pickle
import numpy as np
from pathlib import Path
import statistics
import tensorflow as tf
from tensorflow import keras
from keras.models import Sequential
from keras.layers import Dense



def unpickle(file):
    '''
    Loaded in this way, each of the batch files contains a dictionary with the following elements:
    data -- a 10000x3072 numpy array of uint8s.
    Each row of the array stores a 32x32 colour image.
    The first 1024 entries contain the red channel values, the next 1024 the green, and the final 1024 the blue.
    The image is stored in row-major order, so that the first 32 entries of the array are the red channel values of the first row of the image.
    labels -- a list of 10000 numbers in the range 0-9. The number at index i indicates the label of the ith image in the array data.
    '''
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

print("Turning training data from uint8 to float")
tr_data = tr_data.astype(float)
print("Done!\n")

print("Turning test data from uint8 to float")
te_data = te_data.astype(float)
print("Done!\n")


def cifar_10_evaluate(pred, gt):
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
            right_labels = right_labels + 1

    return (right_labels / gt_len)


def turn_labels_to_single_binary(labels):
    binary_labels = []
    print("turning labels into binary")
    for label in labels:
        if label == 0:
            binary_labels.append(0b1000000000)
        elif label == 1:
            binary_labels.append(0b0100000000)
        elif label == 2:
            binary_labels.append(0b0010000000)
        elif label == 3:
            binary_labels.append(0b0001000000)
        elif label == 4:
            binary_labels.append(0b0000100000)
        elif label == 5:
            binary_labels.append(0b0000010000)
        elif label == 6:
            binary_labels.append(0b0000001000)
        elif label == 7:
            binary_labels.append(0b0000000100)
        elif label == 8:
            binary_labels.append(0b0000000010)
        elif label == 9:
            binary_labels.append(0b0000000001)
    print("Done!")
    print("Binary labels length: ", len(binary_labels))

    return binary_labels







# Neural network stuff
model = Sequential()
# first hidden layer
model.add(Dense(20, input_dim=3072, activation='relu'))
# output layer
model.add(Dense(1,activation='relu'))
model.compile(optimizer='sgd', loss='mse', metrics=['mse'])


def cifar_10_MLP_train(trdata, trlabels):
    '''
    trains MLP classifier for the CIFAR data
    '''
    # turn labels diagonally
    trlabels = np.vstack(trlabels)

    model.fit(trdata, trlabels, epochs=3, verbose=1)

    return

def cifar_10_MLP_test(x,net):
    '''
    estimates the label for the given input x (can be multiple rows)
    '''

    predict_label = net.predict(x)
    print(predict_label)
    print(predict_label.shape)
    return predict_label

def main():
    # turning labels into binary form
    cifar_10_MLP_train(tr_data,tr_labels)

    prediction_labels = []
    prediction_labels.append(cifar_10_MLP_test(te_data,model))

    print("current prediction labels: ", prediction_labels)
    print("Evaluation: ", cifar_10_evaluate(prediction_labels,te_labels))

main()