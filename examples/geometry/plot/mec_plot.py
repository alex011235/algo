#!/usr/bin/python
# alex011235
# https://github.com/alex011235/algorithm>Algorithm
# https://plotly.com/python/network-graphs/

import pandas as pd
import plotly.graph_objects as go

df_res = pd.read_csv('convex_hull_in1.csv')
def_circle = pd.read_csv('mec_out1.csv')

x_in = df_res['x']
y_in = df_res['y']

x = def_circle['x']
y = def_circle['y']
r = def_circle['radius']

xc1 = x - r
yc1 = y - r
xc2 = x + r
yc2 = y + r

points = go.Scatter(x=x_in, y=y_in, mode='markers', hoverinfo='text',
                    marker=dict(showscale=False,
                                colorscale='sunset',
                                reversescale=True,
                                size=12, colorbar=dict(thickness=15, xanchor='left', titleside='right'),
                                line_width=1))

# Create figure

fig = go.Figure(data=[points],
                layout=go.Layout(
                    title='',
                    titlefont_size=16,
                    showlegend=False,
                    hovermode='closest',
                    margin=dict(b=20, l=5, r=5, t=40),
                    annotations=[dict(
                        text="",
                        showarrow=False,
                        xref="paper", yref="paper",
                        x=0.005, y=-0.002)],
                    xaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
                    yaxis=dict(showgrid=False, zeroline=False, showticklabels=False))
                )

# Add shapes
fig.add_shape(type="circle",
              xref="x", yref="y",
              x0=min(xc1), y0=min(yc1),
              x1=max(xc2), y1=max(yc2),
              line_color="LightSeaGreen",
              )

fig.show()
