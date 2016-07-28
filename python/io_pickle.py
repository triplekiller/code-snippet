#!/usr/bin/env python3

# Code tells you how, comment tells you why

import pickle

shop_list_file = 'shoplist.data'
shop_list = ['apple', 'mango', 'carrot']

f = open(shop_list_file, 'wb')
pickle.dump(shop_list, f)
f.close()

del shop_list

f = open(shop_list_file, 'rb')
store_list = pickle.load(f)
print(store_list)
