/*
 * Interaction
 */

function Interaction(pp, pn) {

  this.paper  = pp;
  this.pencil = pn;
  this.x = 0;
  this.y = 0;
  this.color = 'rgba(0, 0, 0, ';

}

Interaction.prototype = {

  setPencil: function(pencil) {
    this.pencil = pencil;
  },

  setColor: function(color) {
    this.color = 'rgba(' + color.R + ',' + color.G + ',' + color.B + ',';
  },

  calD_l: function() {
  
    var h_max = this.paper.getH_max(this.x, this.y);
    var h_min = this.paper.getH_min(this.x, this.y);

    var p_a = this.pencil.getAvgPressure();
    var d_l = h_max - h_min*p_a;
    d_l = d_l < h_min ? h_min : d_l;

    return d_l;

  },

  calH_k: function(d_l) {
  
    var h_k = this.paper.getH(this.x, this.y) - 
              this.pencil.da()*this.paper.getW() * d_l;
    h_k = h_k < 0 ? 0 : h_k;

    return h_k;

  },

  calB_v: function(d_l) {
  
    var t_v = this.paper.getT_v(this.x, this.y);

    if (this.paper.getH(this.x, this.y) > d_l)
      return t_v;

    var hp_max = this.paper.getHp_max(this.x, this.y);
    var hp_min = this.paper.getHp_min(this.x, this.y);

    var divider = hp_max - hp_min;
    divider = Math.abs(divider) < Const.ZERO ? 1 : divider;

    var b_v = this.pencil.ba() * t_v * (hp_max - d_l) / divider;
    b_v = b_v < 0 ? 0 : b_v;

    return b_v;
  
  },

  calT_k: function(b_k) {

    var t_k = (this.pencil.getGP() +
               this.pencil.getCP() +
               this.pencil.getWP()) * b_k;
    return t_k;
  
  },

  // Takes the coordinate of the center of the pencil currently, and then
  // calculates the points affected, returns the affected point set with
  // the following object:
  //
  // {
  //   x : the x coordinate of the point.
  //   y : the y coordinate of the point.
  //   fillStyle : the color of the point.
  // }
  actWithPoint: function(mx, my) {
  
    var points = this.pencil.points;
    var d_l, b_v, h_k, b_k, t_k, grey;

    for (var i = 0; i < points.length; ++i) {

      this.x = mx + points[i].x;
      this.y = my + points[i].y;

      d_l = this.calD_l();
      b_v = this.calB_v(d_l);
      this.paper.setB_v(mx + points[i].x, my + points[i].y, b_v);

    }

    var ps = [];
    for (var i = 0; i < points.length; ++i) {

      this.x = mx + points[i].x;
      this.y = my + points[i].y;

      d_l = this.calD_l();
      h_k = this.calH_k(d_l);
      b_k = this.paper.getB_k(
        mx + points[i].x, 
        my + points[i].y, 
        this.pencil.getAvgPressure()
      );
      t_k = this.calT_k(b_k);

      this.paper.updateH(mx + points[i].x, my + points[i].y, h_k);
      this.paper.updateT(mx + points[i].x, my + points[i].y, t_k);

      grey = this.paper.getT_k(mx + points[i].x, my + points[i].y) / 1000.0;
      grey = grey > 1 ? 0 : grey;
      
      // canvas.fillStyle = this.color + grey + ')';
      // canvas.fillRect(mx + points[i].x, my + points[i].y, 1, 1);
      ps.push({
        x : mx + points[i].x,
        y : my + points[i].y,
        fillStyle : this.color + grey + ')',
      });

    }

    return ps;
  
  },

  // The coordinates of the points set should have the following
  // format:
  //
  // {
  //   x: the x coordinate of the point.
  //   y: the y coordinate of the point.
  // }
  actWithPoints: function(points) {
  
    for (var i = 0; i < points; ++i) {
      this.actWithPoint(points[i].x, points[i].y);
    }
  
  }, 

}
