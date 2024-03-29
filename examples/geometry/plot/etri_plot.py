#!/usr/bin/python
# alex011235
# https://github.com/alex011235/algorithm>Algorithm
# https://plotly.com/python/network-graphs/

import pandas as pd
import plotly.graph_objects as go

df_res = pd.read_csv('etri_out1.csv')
def_circle = pd.read_csv('mec_out1.csv')

x_in = df_res['x']
y_in = df_res['y']
label = df_res['Label']

x1 = x_in[label == 1]  # Raw points
y1 = y_in[label == 1]
x2 = x_in[label == 2]  # Triangle
y2 = y_in[label == 2]

x = def_circle['x']
y = def_circle['y']
r = def_circle['radius']

xc1 = x - r
yc1 = y - r
xc2 = x + r
yc2 = y + r

points = go.Scatter(x=x1, y=y1, mode='markers', hoverinfo='text',
                    marker=dict(showscale=False,
                                colorscale='sunset',
                                reversescale=True, color=label,
                                size=12, colorbar=dict(thickness=15, xanchor='left', titleside='right'),
                                line_width=1))

triangle = go.Scatter(x=x2, y=y2,
                      marker=dict(showscale=False,
                                  colorscale='aggrnyl',
                                  reversescale=True, color=label,
                                  size=8, colorbar=dict(thickness=15, xanchor='left', titleside='right'),
                                  line_width=1),
                      line=dict(color="#ff5500", width=2))

# Create figure

fig = go.Figure(data=[points, triangle],
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
