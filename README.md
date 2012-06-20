#Graphite Pencil

The graphite pencil implementation and demonstration in Qt and JavaScript.

## TODOs

The project was originally intended to implement the graphite pencil. But as time goes by, more and more ideas pop out of my mind. I want to make it a little more interesting rather than just a graphtie pencil demostration.

The TODOs is devided into two main groups.

### Algorithm

1. When the mouse moves fast, the line drawn by the graphite pencil would not be continuous since the sampling process of the mouse coordinate only executes in a specific period of time. A proper solution is to use proper interpolation to make the line looks more continuous.

2. Given a path, use graphite pencil to draw with the path.

3. Given an area, use graphite pencil to fill the area in a proper way.

4. Find a better way to use graphite pencil effect to shadow a given image.

5. Find a better way to accomplish the edge detection and make it accord to the shadow of the given image.

6. Implement blender and eraser.


### UI

1. Design a better user interface. The current version is only for testing, which is not user-friendly or can be called as art.

2. Add blender and eraser functionality.

3. Add selection functionality.
