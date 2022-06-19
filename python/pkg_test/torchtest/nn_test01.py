import torch
import torchvision
import torch.nn as nn
# import matplotlib.pyplot as plt
import torch.autograd.variable as Variable
import torch.utils.data as Data

class Net(nn.Module):
    def __init__(self):
        super(Net, self).__init__()
        self.conv1=nn.Sequential(
            nn.Conv2d(
                in_channels=1,
                out_channels=16,
                kernel_size=2,
            ),
            nn.ReLU(),
            nn.MaxPool2d(kernel_size=2),
        )
        self.conv2=nn.Sequential(
             nn.Conv2d(
                in_channels=16,
                out_channels=32,
                kernel_size=2,
            ),
            nn.ReLU(),
            nn.MaxPool2d(kernel_size=2),
        )
        self.fc=nn.Linear(32*7*7,10)

    def forward(self, x):
        x=self.conv1(x),
        x=self.conv2(x),
        x=x.view(x.size(0),-1),
        return self.fc(x)

print(Net())