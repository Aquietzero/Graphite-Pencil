/*
 * Interpolation
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
        x : start.x + i * step_x,
        y : start.y + i * step_y,
      });
    }

    return points;
  
  },

}
