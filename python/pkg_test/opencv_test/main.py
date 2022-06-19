# -*- coding: utf-8 -*-
import numpy as np
import cv2
from matplotlib import pyplot as plt

#
# img = cv2.imread('cat.jpg', cv2.IMREAD_COLOR)
#
# print("================打印一下图像的属性===============")
# print("图像对象的类型{}".format(type(img)))
# print(img.shape)
# print("图像宽度：{} pixels".format(img.shape[1]))
# print("图像高度：{} pixels".format(img.shape[0]))
# print("通道：{} ".format(img.shape[2]))
# print("图像分辨率：{} ".format(img.size))
# print("数据类型：{} ".format(img.dtype))




# img = cv2.imread('cat.jpg', cv2.IMREAD_COLOR)
#
# # plt.imshow(img)
# # plt.imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
# gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
# plt.imshow(gray, cmap = 'gray')
#
# # 隐藏坐标系
# plt.axis('off')
# # 展示图片
# plt.show()
# plt.savefig('cat_gray_01.jpg')




# img = cv2.imread('cat.jpg', cv2.IMREAD_COLOR)
#
# # cv2.namedWindow('image_win', flags = cv2.WINDOW_AUTOSIZE | cv2.WINDOW_KEEPRATIO | cv2.WINDOW_GUI_EXPANDED)
# cv2.imshow('image_win', img)
#
# print("请按任意键关闭窗口")
#
# key_pressed = cv2.waitKey(0)
#
# cv2.destroyWindow('image_win')






# img = cv2.imread('cat.jpg', cv2.IMREAD_COLOR)
#
# # cv2.namedWindow('image_win', flags = cv2.WINDOW_AUTOSIZE | cv2.WINDOW_KEEPRATIO | cv2.WINDOW_GUI_EXPANDED)
# cv2.imshow('image_win', img)
#
# key_pressed = cv2.waitKey(5000)
#
# print("有按键摁下或已超时")
#
# print("Key pressed : {}".format(key_pressed))
#
# cv2.destroyWindow('image_win')




# img_color = cv2.imread('cat.jpg', cv2.IMREAD_COLOR)
# img_gray = cv2.imread('cat.jpg', cv2.IMREAD_GRAYSCALE)
# img_alpha = cv2.imread('cat.jpg', cv2.IMREAD_UNCHANGED)
#
# cv2.namedWindow('image_color', flags = cv2.WINDOW_NORMAL | cv2.WINDOW_KEEPRATIO | cv2.WINDOW_GUI_EXPANDED)
# cv2.imshow('image_color', img_color)
#
# cv2.namedWindow('image_gray', flags = cv2.WINDOW_NORMAL | cv2.WINDOW_KEEPRATIO | cv2.WINDOW_GUI_EXPANDED)
# cv2.imshow('image_gray', img_gray)
#
# cv2.namedWindow('image_alpha', flags = cv2.WINDOW_NORMAL | cv2.WINDOW_KEEPRATIO | cv2.WINDOW_GUI_EXPANDED)
# cv2.imshow('image_alpha', img_alpha)
#
# print("请按 按键e关闭窗口")
#
# while True:
#     key_pressed = cv2.waitKey(100)
#     if key_pressed >= 0:
#         print("Key pressed : {}".format(key_pressed,chr(key_pressed)))
#     if key_pressed == ord('e'):
#         break
#
# cv2.destroyWindows()



# 彩图灰度图拼接，未成功
# img_color = cv2.imread('cat.jpg', cv2.IMREAD_COLOR)
# img_gray = cv2.imread('cat.jpg', cv2.IMREAD_GRAYSCALE)
#
# print(img_color[100:110, 100:110, 0:3])
# print(img_gray[100:110, 100:110,])
#
# # img_final = np.hstack((img_color, img_gray))
# # cv2.namedWindow('image_win', flags = cv2.WINDOW_NORMAL | cv2.WINDOW_KEEPRATIO | cv2.WINDOW_GUI_EXPANDED)
# # cv2.imshow('image_win', img_final)
# #
# # key_pressed = cv2.waitKey(5000)
# #
# # print("有按键摁下或已超时")
# #
# # print("Key pressed : {}".format(key_pressed))
# #
# # cv2.destroyWindow('image_win')




# img_color = cv2.imread('cat.jpg', cv2.IMREAD_COLOR)
#
# cv2.imwrite('cat_cvsave.png',img_color)





# img_color = cv2.imread('cat.jpg', cv2.IMREAD_COLOR)
#
# for quality in range(0, 100, 10):
#     cv2.imwrite('cat_cvimwrite_{}.jpg'.format(quality), img_color, [cv2.IMWRITE_JPEG_QUALITY, quality])






img_color = cv2.imread('cat.jpg', cv2.IMREAD_COLOR)

for cmpi in range(0, 10):
    cv2.imwrite('cat_cvimwrite_{}.png'.format(cmpi), img_color, [cv2.IMWRITE_PNG_COMPRESSION, cmpi])