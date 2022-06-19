# torch 入门学习
# Pytorch 官方 60 分钟入门学习
import torch

# x = torch.empty(5, 3)
# print(x)



# x = torch.ones(2, 2, requires_grad=True)  # set requires_grad=True to track computation with it
# print(x)
# y = x + 2
# print(y)
# print(y.grad_fn)   # y was created as a result of an operation, so it has a grad_fn.
#
# z = y * y * 3   # z = 3*(x+2)^2
# out = z.mean()   # out = 0.25*3*(x+2)^2
#
# print(z, out)
#
# a = torch.randn(2, 2)
# a = ((a * 3) / (a - 1))
# print(a.requires_grad)
# a.requires_grad_(True)
# print(a.requires_grad)
# b = (a * a).sum()
# print(b.grad_fn)
#
# out.backward()   # out.backward() is equivalent to out.backward(torch.tensor(1.))
# # Print gradients d(out)/dx
# print(x.grad)   # d(out)/dx = 1.5*(x+2)




# vector-Jacobian product:
x = torch.randn(3, requires_grad=True)
y = x * 2
while y.data.norm() < 1000:  # y.data.norm 指 y 的 L2 范数
    y = y * 2
print(y)
v = torch.tensor([0.1, 1.0, 0.0001], dtype=torch.float)
y.backward(v)
print(x.grad)

print(x.requires_grad)
print((x ** 2).requires_grad)
# stop autograd from tracking history on Tensors
with torch.no_grad():
    print((x ** 2).requires_grad)

# using .detach() to get a new Tensor with the same content but that does not require gradients:
print(x.requires_grad)
y = x.detach()
print(y.requires_grad)
print(x.eq(y).all())



