
function Painter(dom_id) {

  var dom = document.getElementById(dom_id);

  this.dom_id = dom_id;
  this.canvas = dom.getContext('2d');

  this.width  = dom.width;
  this.height = dom.height;

}

Painter.prototype = {

  DEFAULT_ELEMS: [
    new Elem( 0,  2, 0.5, 0.5),
    new Elem( 1,  1, 0.5, 0.5),
    new Elem( 1, -1, 0.5, 0.5),
    new Elem( 0, -2, 0.5, 0.5),
    new Elem(-1, -1, 0.5, 0.5),
    new Elem(-1,  1, 0.5, 0.5)
  ],

  init: function() {

    var elems = this.DEFAULT_ELEMS;
    this.paper  = new Paper(this.width, this.height, 2000, 0.5, 0.5);

    this.pencil = new Pencil(0.5, 0.1, 0.9, 0.5, 0.05, elems);
    this.pencil.getPoints();

    this.interaction = new Interaction(this.paper, this.pencil);

    this._initShaperGetter();
    this._bindDrawEvent();
    this._bindShapeGetterEvent();

  },

  _initShaperGetter: function() {

    this.shape = new ShapeGetter('shape');
    this.shape.init();

  },

  _bindDrawEvent: function() {

    var _that = this;
    var is_down = false;
    var canvas = $('#' + this.dom_id);

    canvas.mousedown(function() {
      is_down = true;
    });

    canvas.mouseup(function() {
      is_down = false;
    });

    canvas.mousemove(function(e) {

      if (is_down) {
        var x = e.clientX - $(this).offset().left;
        var y = e.clientY - $(this).offset().top;
        _that.interaction.act(x, y, _that.canvas);
      }

    });

  },

  _bindShapeGetterEvent: function() {
  
    var _that = this;
    var resetButton  = $('#resetShape');
    var commitButton = $('#commitShape');

    var resetShapeHandler = function() {
      _that.shape.reset();
    }

    var commitShapeHandler = function() {
      _that.pencil = new Pencil(0.5, 0.1, 0.9, 0.5, 0.05, _that.shape.vertices);
      _that.pencil.getPoints();
      _that.interaction.setPencil(_that.pencil);
    }

    resetButton.click(resetShapeHandler);
    commitButton.click(commitShapeHandler);

  },

}
