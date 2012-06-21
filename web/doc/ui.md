# UI components and their functionalities

This can be more a concepts and solutions' brain storm rather than the documentation in detail. On the other way, this file can be regarded as the UI TODOs file. Although the functionalities are quite simple now, I have the following ideas to enrich them.



## Components

Since all of them are still in the conceptional phase, so it would be hard to group them in an appearence level. I listed the following components of the graphtie pencil painter by brain storm.


### Paint Area

Undoubtably, the most important part of a painter application is the paint area in the middle. User can draw or create any effects they want in this area. Since I really want to adopt the idea of layers, user can actually draw things on different layers.

I think layer can be implemented by layer buffers. A layer corresponds to a specific layer buffer, which keeps track of the `{ position: color }` pair for each pixel of the canvas on that layer. I will explain this model in detail with the one dimensional example as below:

    column            1     2     3     4     5     6     7     8     9   
    layer buffer 1 [     |     | c13 |     |     |     |     |     |     ] A(1)
    layer buffer 2 [     |     | c23 |     |     |     |     |     |     ] A(2)
            :                                 :
            :                                 :
            :                                 :
    layer buffer n [     |     |     |     | cn5 |     |     |     |     ] A(n)
    canvas         [     |     | c3  |     | c5  |     |     |     |     ]

Each layer corresponds to an alpha value, which is the alpha value of all the colors on that layer. By default, the higher layer covers the lower one. But if the higher layer has a different alpha value rather than 1, then a concept borrowed from OpenGL is adopted. Blending functions are used to calculate the final color of each pixel in the canvas. As we know, the blending function is shown as below:

    F = A(n-1) * S + A(n) * D

where `A(n)` is the alpha value of the nth layer.

**When it comes to rendering, there would be impossible to scan each of the pixel of each layer every time. So a more feasible way to deal with the problem is to render those pixels which are changed.**


### Layer Controller

Since the layer concept is available in rendering, so it is in manipulating. This is the advanced technique for advanced user. User can easily add layer, delete layer and select the current working layer throught the layer controller panel.


### Color Picker

Although this panel is already finished, it is still so urly and leck of color information. The following function should be added.

1. Shows the RGB value when picking color.
2. Allows the user to input RGB color rather than just moving the mouse around to pick.


### Paper Configuration Panel

Add a panel for user to configure the paper.


### Pencil Configuration Panel

Add a panel for user to configure pencil.


### Ruler
