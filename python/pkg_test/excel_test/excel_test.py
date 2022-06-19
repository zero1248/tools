# -*- coding: utf-8 -*-
import xlrd
import xlwt
import xlutils

#open xls document
book = xlrd.open_workbook("xlrd_test.xls")
print("表单数量：", book.nsheets)
print("表单名称：", book.sheet_names())

#get the 1st sheet
sh = book.sheet_by_index(0)
print("表单 %s 共 %d 行 %d 列"%(sh.name, sh.nrows, sh.ncols))
print("第二行第三列：", sh.cell_value(1, 2))
#traverse all the sheets
for s in book.sheets():
    for r in range(s.nrows):
        #output the dedicated rows
        print(s.row(r))


# create xls file object
wb = xlwt.Workbook()
# add a new sheet
sh = wb.add_sheet('A Test Sheet')
# add datas
sh.write(0, 0, 1234.56)
sh.write(1, 0, 8888)
sh.write(2, 0, 'hello')
sh.write(2, 1, 'world')
# save file
wb.save('xlwt_test.xls')

from xlrd import open_workbook
from xlutils.copy import copy
# open file
rb = open_workbook("xlrd_test.xls")
# copy
wb = copy(rb)
wb.add_sheet('test sheet')
# select sheet
s = wb.get_sheet(1)
# write datas
s.write(0, 1, 'new data')
# save file
wb.save('xlutils_test.xls')


