
function Painter(dom_id) {

  var dom = document.getElementById(dom_id);

  this.dom_id = dom_id;
  this.canvas = dom.getContext('2d');

  this.width  = dom.width;
  this.height = dom.height;

}

Painter.prototype = {

  DEFAULT_ELEMS: [
    new Elem(  0.5,   0.5, 1.0, 1.0),
    new Elem(  0.5,  2.5, 0.5, 0.5),
    new Elem( 1.5,  1.5, 0.5, 0.5),
    new Elem( 1.5, -1.5, 0.5, 0.5),
    new Elem(  0.5, -2.5, 0.5, 0.5),
    new Elem(-1.5, -1.5, 0.5, 0.5),
    new Elem(-1.5,  1.5, 0.5, 0.5)
  ],

  init: function() {

    var elems = this.DEFAULT_ELEMS;
    this.paper  = new Paper(this.width, this.height, 2000, 0.5, 0.5);

    this.pencil = new Pencil(0.5, 0.1, 0.9, 0.5, 0.05, elems);
    this.pencil.getPoints();

    this.interaction = new Interaction(this.paper, this.pencil);

    this._initColorPicker();
    this._initShapeGetter();
    this._bindDrawEvent();
    this._bindColorPickerEvent();
    this._bindShapeGetterEvent();

  },

  _initShapeGetter: function() {

    this.shapeGetter = new ShapeGetter('shapeGetter');
    this.shapeGetter.init();

  },

  _initColorPicker: function() {
  
    this.colorPicker = new ColorPicker('colorPicker', 'colorPreview');
    this.colorPicker.init();

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

        x = Math.floor(x);
        y = Math.floor(y);

        _that.interaction.act(x, y, _that.canvas);
      }

    });

  },

  _bindShapeGetterEvent: function() {
  
    var _that = this;
    var resetButton  = $('#resetShapeGetter');
    var commitButton = $('#commitShapeGetter');

    var resetShapeGetterHandler = function() {
      _that.shapeGetter.reset();
    }

    var commitShapeGetterHandler = function() {
      _that.pencil = new Pencil(0.5, 0.1, 0.9, 0.5, 0.05, _that.shapeGetter.vertices);
      _that.pencil.getPoints();
      _that.interaction.setPencil(_that.pencil);
    }

    resetButton.click(resetShapeGetterHandler);
    commitButton.click(commitShapeGetterHandler);

  },

  _bindColorPickerEvent: function() {

    var _that = this;
    var commitButton = $('#commitColor');

    var commitShapeGetterHandler = function() {
      _that.interaction.setColor(_that.colorPicker.color);
    }

    commitButton.click(commitShapeGetterHandler);
 
  },

}
