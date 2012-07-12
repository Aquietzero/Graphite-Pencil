/*
 * Interpolation
 *
 * Several interpolation methods are defined in the Interpolation
 * namespace. Nearly all of the interpolation methods take the
 * coordinate of the start and end point and the step of course,
 * then the interpolation methods returns an array of points as the
 * result of the interpolation. One thing that needs to pay attention
 * is that the coordinates of the points are all integers, which is
 * better for canvas rendering.
 */

var Interpolation = {

  line: function(start, end, step) {

    dx = end.x - start.x;
    dy = end.y - start.y;

    step_x = dx / (step - 1);
    step_y = dy / (step - 1);

    var points = [];
    for (var i = 0; i < step; ++i) {
      points.push({
        x : Math.floor(start.x + i * step_x),
        y : Math.floor(start.y + i * step_y),
      });
    }

    return points;
  
  },

}
