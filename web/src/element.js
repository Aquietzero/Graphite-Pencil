/*
 * Elem is the basic unit of the whole calculation process.
 *
 * x: The coordinate of the x-axis.
 * y: The coordinate of the y-axis.
 * c: The pressure coefficient which ranges from 0 to 1.
 * p: The pressure.
 */
function Elem(vx, vy, vc, vp) {

  this.x = typeof vx === 'undefined' ? 0 : vx;
  this.y = typeof vy === 'undefined' ? 0 : vy;
  this.c = typeof vc === 'undefined' ? 0 : vc;
  this.p = typeof vp === 'undefined' ? 0 : vp;

}

Elem.prototype = {

  copy: function() {

    return new Elem(this.x, this.y, this.c, this.p);

  },

  compareTo: function(other) {

    var dx = this.x - other.x;
    var dy = this.y - other.y;

    if (dx < -Const.ZERO)
      return -1;
    else if (dx > Const.ZERO)
      return 1;
    else {
      if (dy < -Const.ZERO)
        return -1;
      else if (dy > Const.ZERO)
        return 1;
      else
        return 0;
    }
    
  },

  /* Simple linear interpolation
   *
   *     *--------------*----------------*
   *     ^              ^                ^
   *    e1             this             e2
   */
  setByLinearInterpolation: function(e1, e2, pressure) {
    
    var ds = Math.sqrt(Math.pow(e1.x - e2.x, 2) + Math.pow(e1.y - e2.y));
    var d  = Math.sqrt(Math.pow(e1.x - this.x, 2) + Math.pow(e1.y - this.y));

    if (ds < Const.ZERO)
      return false;
    this.c = d / ds * (e2.c - e1.c) + e1.c;
    this.p = pressure * this.c;

  },

  /* Barycentric interpolation
   *           
   *              * e1
   *             /  `
   *            /     `
   *           /        `
   *          /  * this   `
   *         /              `
   *        *-----------------*
   *       e2                  e3
   *
   */
  setByBarycentricInterpolation: function(e1, e2, e3, pressure) {
    
    var x1 = e1.x, y1 = e1.y;
    var x2 = e2.x, y2 = e2.y;
    var x3 = e3.x, y3 = e3.y;

    var det = (y2 - y3)*(x1 - x3) + (x3 - x2)*(y1 - y3);

    var lambda1 = ((y2 - y3)*(this.x - x3) + (x3 - x2)*(this.y - y3)) / det;
    var lambda2 = ((y3 - y1)*(this.x - x3) + (x1 - x3)*(this.y - y3)) / det;
    var lambda3 = 1 - lambda1 - lambda2;

    this.c = lambda1*e1.c + lambda2*e2.c + lambda3*e3.c;
    this.p = pressure * this.c;

  },

  isInside: function(e1, e2, e3) {
  
    var e_1 = (e2.x - e1.x)*(this.y - e1.y) - (this.x - e1.x)*(e2.y - e1.y); 
    var e_2 = (e3.x - e2.x)*(this.y - e2.y) - (this.x - e2.x)*(e3.y - e2.y); 
    var e_3 = (e1.x - e3.x)*(this.y - e3.y) - (this.x - e3.x)*(e1.y - e3.y); 

    if (e_1 >= 0 && e_2 >= 0 && e_3 >= 0 ||
        e_1 <= 0 && e_2 <= 0 && e_3 <= 0)
      return true;
    return false;

  },

}
