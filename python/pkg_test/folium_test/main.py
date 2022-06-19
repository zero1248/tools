# -*- coding: utf-8 -*-

import folium
# import pandas as pd

print(folium.__version__)

# define the world map
world_map = folium.Map()

# define the national map
national_map = folium.Map(location=[35.3, 100.6], zoom_start=4)

# define the beijing map
beijing_map = folium.Map(location=[39.93, 116.40], zoom_start=10)

# display world map


# save
world_map.save('world_map.html')
national_map.save('national_map.html')
beijing_map.save('beijing_map.html')

# m.save('index.html')
#
# folium.Map(
#     location=[45.5236, -122.6750],
#     tiles='Stamen Toner',
#     zoom_start=13
# )
