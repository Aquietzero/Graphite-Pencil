/*
 * Paper
 */

function Paper(w, h, fv, pw, pm) {

  this.width  = w;
  this.height = h;
  this.f_v    = fv;
  this.W      = pw;
  this.M      = pm;

  this.grains = (function(w, h) {

    var gs = new Array(w);

    for (var i = 0; i < w; ++i) {
      gs[i] = new Array(h);
      for (var j = 0; j < h; ++j) 
        gs[i][j] = new Grain(Math.random());    
    }

    return gs;
  
  })(w, h);

}

Paper.prototype = {
  
  getW: function() { return this.W; },
  getM: function() { return this.M; },

  updateH: function(i, j, gh) {
    this.grains[i][j].updateH(gh);
  },

  updateT: function(i, j, gt) {
    this.grains[i][j].updateT(gt);
  },

  getH: function(i, j) {
    return this.grains[i][j].h;
  },

  getH_max: function(i, j) {

    return Math.max(
      this.grains[i][j].h,
      this.grains[i+1][j].h,
      this.grains[i+1][j+1].h,
      this.grains[i][j+1].h
    );

  },

  getH_min: function(i, j) {

    return Math.min(
      this.grains[i][j].h,
      this.grains[i+1][j].h,
      this.grains[i+1][j+1].h,
      this.grains[i][j+1].h
    );

  },

  getH_sum: function(i, j) {

    return Utils.sum(
      this.grains[i][j].h,
      this.grains[i+1][j].h,
      this.grains[i+1][j+1].h,
      this.grains[i][j+1].h
    );

  },

  getHp_max: function(i, j) {
    return this.getH_max(i, j) - this.getH_min(i, j);
  },

  getHp_min: function(i, j) {
    return 0;
  },

  getHp_sum: function(i, j) {

    var h_max = this.getH_max(i, j);
    return h_max - this.grains[i][j].h     +
           h_max - this.grains[i+1][j].h   + 
           h_max - this.grains[i+1][j+1].h + 
           h_max - this.grains[i][j+1].h;

  },

  getD_k: function(i, j, gh) {

    h_sum = this.getH_sum(i, j);
    if (h_sum < Const.ZERO)
      return 0;
    return gh / h_sum;

  },

  getT_v: function(i, j) {
    return this.f_v * this.getHp_sum(i, j) / 4.0;
  },

  getT_k: function(i, j) {
    return this.grains[i][j].getT_k();
  },

  getL_k: function(i, j) {

    var h = this.grains[i][j].h;
    return this.getD_k(i-1, j, h) * this.getT_v(i-1, j) +
           this.getD_k(i, j-1, h) * this.getT_v(i, j-1) +
           this.getD_k(i-1, j-1, h) * this.getT_v(i-1, j-1) +
           this.getD_k(i, j, h) * this.getT_v(i, j);

  },

  getB_k: function(i, j, p) {

    var h = this.grains[i][j].h;
    var b_k = this.getD_k(i-1, j, h) * this.grains[i-1][j].b +
              this.getD_k(i, j-1, h) * this.grains[i][j-1].b +
              this.getD_k(i-1, j-1, h) * this.grains[i-1][j-1].b +
              this.getD_k(i, j, h) * this.grains[i][j].b;

    return this.grains[i][j].getT_k() > this.getL_k(i, j) ? b_k * Math.pow(this.M, p) : b_k;

  },

  setB_v: function(i, j, bv) {
    this.grains[i][j].setB_v(bv);
  }

}
