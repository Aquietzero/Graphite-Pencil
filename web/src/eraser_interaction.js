/*
 * Eraser Interaction
 */
function EraserInteraction(pp, pn, bc) {
  
  this.paper = pp;
  this.pencil = pn;
  this.x = 0;
  this.y = 0;
  this.color = bc;
}

EraserInteraction.prototype = {
  
  setColor: function(color) {
    this.color = color;
  },

  actWithPoint: function(mx, my) {
    var points = this.pencil.points;
    var grey;

    for (var i = 0; i < points.length; ++i) {
      this.x = mx + points[i].x;
      this.y = my + points[i].y;
    }

    var ps = [];
    for (var i = 0; i < points.length; ++i) {
      this.x = mx + points[i].x;
      this.y = my + points[i].y;

      ps.push({
        x : mx + points[i].x,
        y : my + points[i].y,
        fillStyle : this.color,
      });
    }

    return ps;
  },

  actWithPoints: function(points) {

    for (var i = 0; i < points; ++i) {
      this.actWithPoint(points[i].x, points[i].y);
    }

  },
}
