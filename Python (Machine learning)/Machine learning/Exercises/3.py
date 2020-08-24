import pickle
import numpy as np
from pathlib import Path
import statistics
import scipy.stats


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

def cifar_10_features(x):
    '''
     forms the mean color feature of x. f = [R,G,B]
    :param x: 3072 long row (1 image)
    :return: f
    '''
    '''
    the first 1024 entries contain red,
     next 1024 green,
      last 1024 blue
    '''
    mean_red = statistics.mean(x[0:1023])
    mean_green = statistics.mean(x[1024:2048])
    mean_blue = statistics.mean(x[2049:3073])

    return [mean_red, mean_green, mean_blue]


def cifar_10_bayes_learn(F, labels):
    '''
     computes the normal distribution parameters for the
    samples in F (one line per sample) for each category
     (category specific mean and std). Note that
    the size of mu and sigma must be num of classes × 3.
    The p (prior) probabilities are a vector of
    num of classes × 1, one for each class.
    :param F: Sample line, 3072 long lines, multiple
    :param labels:
    :return: mu, sigma, p #mean, std, prior propabilities
    '''
    '''
    computing the mean and std for colours of class "1"
    '''
    print("computing the mean and std for colours of classes")
    # sort the RGB mean values into their correct classes
    sorting_book = {}
    for label in set(labels):
        sorting_book[label] = {"R" : [], "G" : [], "B" : []}

    for sample_index in range(F.shape[0]):
        label = labels[sample_index]
        r,g,b = cifar_10_features(tr_data[sample_index])
        sorting_book[label]["R"].append(r)
        sorting_book[label]["G"].append(g)
        sorting_book[label]["B"].append(b)

    # calculate the mean and std of each R, G and B for each class
    mean_var_book = {}
    for label in set(labels):
        # set default values for the dict
        mean_var_book[label] = {"Rmean" : 0, "Rvar" : 0, "Gmean" : 0, "Gvar" : 0, "Bmean" : 0, "Bvar" : 0}

    for label in sorting_book:
        mean_var_book[label]["Rmean"] = statistics.mean(sorting_book[label]["R"])
        mean_var_book[label]["Rvar"] = statistics.stdev(sorting_book[label]["R"])
        mean_var_book[label]["Gmean"] = statistics.mean(sorting_book[label]["G"])
        mean_var_book[label]["Gvar"] = statistics.stdev(sorting_book[label]["G"])
        mean_var_book[label]["Bmean"] = statistics.mean(sorting_book[label]["B"])
        mean_var_book[label]["Bvar"] = statistics.stdev(sorting_book[label]["B"])

    print("Done!\n")
    print("Mean and standard deviation look like this: ")
    for label in mean_var_book:
        print("class", label, mean_var_book[label])


    '''
    computing prior probability p for each class
    
    the p for each class is the same 10%
    '''
    p = [1/len(set(labels))] * len(set(labels))
    print("Class spesific p values: ", p)

    '''
    # let's put the means and variables into a list for the return
    return_var_list = []
    for label in mean_var_book:
        return_var_list.append(mean_var_book[label]["Rvar"])
        return_var_list.append(mean_var_book[label]["Gvar"])
        return_var_list.append(mean_var_book[label]["Bvar"])

    return_mean_list = []
    for label in mean_var_book:
        return_mean_list.append(mean_var_book[label]["Rmean"])
        return_mean_list.append(mean_var_book[label]["Gmean"])
        return_mean_list.append(mean_var_book[label]["Bmean"])
    '''


    # :return: mu, sigma, p #mean, std, prior propabilities
    # let's return mu and sigma as the mean_var_book instead
    return mean_var_book, p



def cifar_10_bayes_classify(f,mean_var_book,p):
    '''
    Returns the Bayesian optimal class c
    for the sample f.
    :param f:
    :param mu:
    :param sigma:
    :param p:
    :return:
    '''
    '''
    loop the sample trough calculations of normpdf for each class
    '''
    # normpdf(Xmeanred, CLmeanred, CLvarred)
    fr, fg, fb = cifar_10_features(f)

    current_best_feature_match_label = 0
    current_best_feature_match_calc = 0
    for label in mean_var_book:
        calc = scipy.stats.norm.pdf(fr, mean_var_book[label]["Rmean"],mean_var_book[label]["Rvar"])* \
               scipy.stats.norm.pdf(fg, mean_var_book[label]["Gmean"],mean_var_book[label]["Gvar"])* \
               scipy.stats.norm.pdf(fb, mean_var_book[label]["Bmean"],mean_var_book[label]["Bvar"])*p[label]


        if calc > current_best_feature_match_calc:
            current_best_feature_match_calc = calc
            current_best_feature_match_label = label

    return current_best_feature_match_label


def main():
    mean_var_book, p = cifar_10_bayes_learn(tr_data, tr_labels)

    prediction_labels = []
    for sample_index in range(te_data.shape[0]):
        prediction_labels.append(cifar_10_bayes_classify(te_data[sample_index], mean_var_book, p))

    print("current prediction labels: ", prediction_labels)
    print("Evaluation: ", cifar_10_evaluate(prediction_labels,te_labels))

main()