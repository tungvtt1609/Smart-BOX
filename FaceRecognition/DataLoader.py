import torch
import torchvision
import torch.utils.data as Data
import torchvision.transforms as Transforms
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
from torch.utils.data.sampler import SubsetRandomSampler

import numpy as np
import os
import math
import matplotlib
import matplotlib.pyplot as plt
from PIL import Image

data_rgb_path = ""
data_d_path = ""
class_n = 0


class DataType():
    """Stores the paths to images for a given class"""
    def __init__(self, name, rgb_paths, d_paths):
        self.class_name = name
        self.rgb_paths = rgb_paths
        self.d_paths = d_paths


class ImagePath():
    def __init__(self, rgb_path, d_path):
        self.rgb_path = rgb_path
        self.d_path = d_path


def get_image_paths(facedir):
    image_paths = []
    if os.path.isdir(facedir):
        images = os.listdir(facedir)
        image_paths = [os.path.join(facedir, img) for img in images]

    return image_paths


def get_labels(data):
    images = []
    labels = []
    for i in range(len(data)):
        images += [ImagePath(data[i].rgb_paths[j], data[i].d_paths[j]) for j in range(len(data[i].rgb_paths))]
        labels += [i] * len(data[i].rgb_paths)

    return np.array(images), np.array(labels)


def load_data(data_path, data_path_d):
    dataset = []
    classes = [path for path in os.listdir(data_path) if os.path.isdir(os.path.join(data_path, path))]

    classes_n = len(classes)

    for i in range(classes_n):
        face_dir = os.path.join(data_path, classes[i])
        face_dir_d = os.path.join(data_path_d, classes[i])

        # Get image pathes of this class
        image_paths = get_image_paths(face_dir)
        image_paths_d = get_image_paths(face_dir_d)

        dataset.append(DataType(classes[i], image_paths, image_paths_d))

    train_x, train_y = get_labels(dataset)

    return classes_n, train_x, train_y


def imageRead(path, Type):
    # print(path)
    with open(path, 'rb') as f:
        with Image.open(f) as img:
            if Type == 3:
                img = img.convert('RGB')
            elif Type == 1:
                img = img.convert('L')
            return img


class DataLoader(Data.Dataset):
    def __init__(self, img_paths, labels, transform, loader=imageRead):
        self.img_paths = img_paths
        self.labels = labels
        self.transform = transform
        self.loader = loader

    def __getitem__(self, index):  # return data type is tensor
        rgb_path, d_path = self.img_paths[index].rgb_path, self.img_paths[index].d_path
        label = self.labels[index]

        rgb_img = np.array(imageRead(rgb_path, 3))
        d_img = np.array(imageRead(d_path, 1))
        d_img = np.expand_dims(d_img, axis=2)

        img = np.append(rgb_img, d_img, axis=2)
        img = self.transform(Image.fromarray(img))
        label = torch.from_numpy(np.array(label)).type(torch.LongTensor)

        return img, label

    def __len__(self):  # return the total size of the dataset
        return len(self.labels)


### Split dataset and creat train & valid dataloader ###
def split_dataset(dataset_t, batch, split_ratio):
    num_train = len(dataset_t)
    indices = list(range(num_train))
    split = int(np.floor(split_ratio * num_train))

    #np.random.seed(random_seed)
    np.random.shuffle(indices)

    train_idx, valid_idx = indices[split:], indices[:split]
    train_sampler = SubsetRandomSampler(train_idx)
    valid_sampler = SubsetRandomSampler(valid_idx)

    train_loader = torch.utils.data.DataLoader(dataset_t, batch_size=batch, sampler=train_sampler)
    valid_loader = torch.utils.data.DataLoader(dataset_t, batch_size=batch, sampler=valid_sampler)

    return train_loader, valid_loader


def CreateDataloader(data_path, data_path_d, batch, split_ratio):
    classes_n, train_x, train_y = load_data(data_path, data_path_d)

    transform = Transforms.Compose([
        Transforms.Resize(224),
        Transforms.ToTensor(),
    ])

    dataset = DataLoader(train_x, train_y, transform=transform)

    train_loader, valid_loader = split_dataset(dataset, batch, split_ratio)

    print('Number of classes: %d' % classes_n)
    print('Total images: %d' % len(train_x))
    # print('Total images: %d (split ratio: %.1f)' % (len(train_x), split_ratio) )
    # print('Training images:', len(train_loader))
    # print('Validation images: ', len(valid_loader))

    return classes_n, train_loader, valid_loader
