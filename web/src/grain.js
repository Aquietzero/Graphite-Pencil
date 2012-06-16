/*
 * Grain is the basic element of the paper.
 */

function Grain(h) {

  this.h = h || 0;
  this.t = 0;
  this.b = 0;

}

Grain.prototype = {

  updateH: function(gh) {
    this.h = gh;
  },

  updateT: function(gt) {
    this.t += gt;
  },

  getT_k: function() {
    return this.t;
  },

  setB_v: function(bv) {
    this.b = bv;
  },

}


