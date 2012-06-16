/*
 * Interaction
 */

function Interaction(pp, pn) {

  this.paper  = pp;
  this.pencil = pn;
  this.x = 0;
  this.y = 0;

}

Interaction.prototype = {

  calD_l: function() {
  
    var h_max = this.paper.getH_max(this.x, this.y);
    var h_min = this.paper.getH_min(this.x, this.y);

    var p_a = this.pencil.getAvgPressure();
    var d_l = h_max - h_min*p_a;
    d_l = d_l < h_min ? h_min : d_l;

    return d_l;

  },

  calH_k: function(d_l) {
  
    h_k = this.paper.getH(this.x, this.y) - 
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

    t_k = (this.pencil.getGP() +
           this.pencil.getCP() +
           this.pencil.getWP()) * b_k;
    return t_k;
  
  },

  act: function(mx, my, canvas) {
  
    var points = this.pencil.points;
    var d_l, b_v, h_k, b_k, t_k, grey;

    for (var i = 0; i < points.length; ++i) {

      this.x = mx + points[i].x;
      this.y = my + points[i].y;
      d_l = this.calD_l();
      b_v = this.calB_v(d_l);
      this.paper.setB_v(mx + points[i].x, my + points[i].y, b_v);

    }

    // console.log(points.length);
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

      grey = this.paper.getT_k(mx + points[i].x, my + points[i].y) * this.pencil.getGP() / 1000.0;
      
      canvas.fillStyle = 'rgba(0, 255, 255, ' + grey + ')';
      canvas.fillRect(mx + points[i].x, my + points[i].y, 1, 1);

    }
  
  }

}
