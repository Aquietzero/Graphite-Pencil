/*
 * Pencil
 */

function Pencil(p, d, gp, cp, wp, vs) {

  this.pressure = p;
  this.degree   = d;
  this.g_p      = gp;
  this.c_p      = cp;
  this.w_p      = wp;

  this.vertices = vs;
  this.points   = [];

  // console.log(this.vertices);

}

Pencil.prototype = {

  getGP: function() { return this.g_p; },
  getCP: function() { return this.c_p; },
  getWP: function() { return this.w_p; },

  getBorder: function(e1, e2, e3) {
  
    return {
      left   : Math.min(e1.x, e2.x, e3.x),
      right  : Math.max(e1.x, e2.x, e3.x),
      top    : Math.max(e1.y, e2.y, e3.y),
      bottom : Math.min(e1.y, e2.y, e3.y)
    };
  
  },

  getPointsInTriangle: function(e1, e2, e3) {
  
    var border = this.getBorder(e1, e2, e3);
    var points = [];

    for (var i = border.left; i <= border.right; i += 1)
      for (var j = border.bottom; j <= border.top; j += 1) {
        var elem = new Elem(i, j);
        elem.setByBarycentricInterpolation(e1, e2, e3, this.pressure);

        if (elem.isInside(e1, e2, e3))
          points.push(elem);
      }

    return points;

  },

  getPointsInPolygon: function() {
  
    var v1, v2, v3;
    var ps;
    var points = [];

    v1 = this.vertices[0];
    for (var i = 1; i < this.vertices.length - 1; ++i) {
      v2 = this.vertices[i];
      v3 = this.vertices[i+1];
      
      ps = this.getPointsInTriangle(v1, v2, v3);
      for (var j = 0; j < ps.length; ++j)
        points.push(ps[j]);
    }

    return points;

  },

  getPoints: function() {
    this.points = this.getPointsInPolygon();

    var ps = [];
    this.points = this.points.sort(function(p1, p2) {
      return p1.compareTo(p2);
    });

    var p = this.points[0];
    ps.push(p);
    for (var i = 1; i < this.points.length; ++i) {
      if (this.points[i].compareTo(p) != 0)
        ps.push(this.points[i]);
      p = this.points[i];
    }

    this.points = ps;
  },

  getAvgPressure: function() {
  
    var p_sum = 0;
    for (var i = 0; i < this.points.length; ++i)
      p_sum += this.points[i].p;

    return p_sum / this.points.length;
  
  },

  BVAdjuster: function(bv) {
    return bv;  
  },
  
  update: function(bv) {
  
    var c_bv = this.BVAdjuster(bv);

    for (var i = 0; i < this.vertices.length; ++i) {
      this.vertices[i].x *= 1 + c_bv;
      this.vertices[i].y *= 1 + c_bv;
      this.vertices[i].c *= 1 - c_bv;
    }

    this.getPoints();
    this.pressure *= 1 - bv/5.0;
  
  },

  da: function() { return 0.1; },
  ba: function() { return 0.5; },

}
