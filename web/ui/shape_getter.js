
/*
 *  ,-----------------------------、
 *  |              ^              |
 *  |              |    *         |
 *  |              |      \       |
 *  |              |       \      |
 *  |              |    vertex    |
 *  |  ------------*------------> |
 *  |            / |              |
 *  |           /  |              |
 *  |       origin |              |
 *  |              |              |
 *  |              |              |
 *  `-----------------------------'
 */
function ShapeGetter(dom_id) {

  var dom = document.getElementById(dom_id);

  this.dom_id = dom_id;
  this.canvas = dom.getContext('2d');

  this.width  = dom.width;
  this.height = dom.height;
  this.origin = [dom.width/2, dom.height/2];

  this.vertices = [];

}

ShapeGetter.prototype = {

  isClosed: false,
  
  init: function() {

    this._bindClickEvent();
    this._bindDoubleClickEvent();
    this.reset();
  
  },

  reset: function() {

    var canvas = this.canvas;

    // Clear canvas.
    canvas.fillStyle = '#333';
    canvas.fillRect(0, 0, this.width, this.height);

    canvas.strokeStyle = '#f00';

    canvas.beginPath();

    // Draw cross in the middle.
    canvas.moveTo(this.origin[0], this.origin[1]);
    canvas.lineTo(this.origin[0] - 5, this.origin[1]);
    canvas.moveTo(this.origin[0], this.origin[1]);
    canvas.lineTo(this.origin[0] + 5, this.origin[1]);
    canvas.moveTo(this.origin[0], this.origin[1]);
    canvas.lineTo(this.origin[0], this.origin[1] - 5);
    canvas.moveTo(this.origin[0], this.origin[1]);
    canvas.lineTo(this.origin[0], this.origin[1] + 5);

    canvas.closePath();
    canvas.stroke();

    this.isClosed = false;
    this.vertices = [new Elem(0, 0, 1.0, 1.0)];
    this.verticesOriginal = [];
    
  },

  _bindClickEvent: function() {

    var _that = this;
    $('#' + this.dom_id).click(function(e) {

      if (_that.isClosed)
        return;

      // Get (x, y).
      var x = e.clientX - $(this).offset().left;
      var y = e.clientY - $(this).offset().top;
      _that.verticesOriginal.push({ x:x, y:y });

      // Draw the line between (x, y) and (x_p, y_p).
      if (_that.verticesOriginal.length > 1) {
        var length = _that.verticesOriginal.length;
        var begin  = _that.verticesOriginal[length - 1];
        var end    = _that.verticesOriginal[length - 2];
        _that._drawLine(begin, end);
      }
      
      // Draw the point (x, y).
      _that._drawPoint({ x:x, y:y });

      x = _that._convertX(x);
      y = _that._convertY(y);

      console.log(x, y);
      _that.vertices.push(new Elem(x, y, 0.5, 0.5));

    });

  },

  _bindDoubleClickEvent: function() {

    var _that = this;

    $('#' + this.dom_id).dblclick(function(e) {

      if (_that.isClosed)
        return;

      // Never allow to close the polygon if the number of
      // vertices if less than 2.
      if (_that.verticesOriginal.length > 2) {

        // Draw the line between (x_0, y_0) and (x_n, y_n).
        var length = _that.verticesOriginal.length;
        var begin  = _that.verticesOriginal[length - 1];
        var end    = _that.verticesOriginal[0];
        _that._drawLine(begin, end);

        _that.isClosed = true;
        _that.vertices.pop();
        _that.verticesOriginal.pop();
      }
    
    });
  
  },

  _drawLine: function(begin, end) {

    var canvas = this.canvas;

    canvas.strokeStyle = '#fff';
    canvas.beginPath();
    canvas.moveTo(begin.x, begin.y);
    canvas.lineTo(end.x, end.y);
    canvas.closePath();
    canvas.stroke();

  },

  _drawPoint: function(point) {

    var canvas = this.canvas;

    canvas.fillStyle = '#fff';
    canvas.beginPath();
    canvas.arc(point.x, point.y, 3, 0, Math.PI*2, true);
    canvas.closePath();
    canvas.fill();

  },

  _convertX: function(x) {
    return (x - this.origin[0]) * 10 / this.width;
  },

  _convertY: function(y) {
    return (this.origin[1] - y) * 10 / this.height;
  },

}
