
function Painter(dom_id) {

  var dom = document.getElementById(dom_id);

  this.dom_id = dom_id;
  this.canvas = dom.getContext('2d');

  this.width  = dom.width;
  this.height = dom.height;

  this.canvas_color = 'rgba(255, 255, 255, 1)';
}

Painter.prototype = {

  DEFAULT_ELEMS: [
    new Elem( 0.5,  0.5, 1.0, 1.0),
    new Elem( 0.5,  2.5, 0.5, 0.5),
    new Elem( 1.5,  1.5, 0.5, 0.5),
    new Elem( 1.5, -1.5, 0.5, 0.5),
    new Elem( 0.5, -2.5, 0.5, 0.5),
    new Elem(-1.5, -1.5, 0.5, 0.5),
    new Elem(-1.5,  1.5, 0.5, 0.5)
  ],

  init: function() {

    var elems = this.DEFAULT_ELEMS;
    this.paper  = new Paper(this.width, this.height, 2000, 0.5, 0.5);

    this.pencil = new Pencil(0.5, 0.1, 0.9, 0.5, 0.05, elems);
    this.pencil.getPoints();

    this.interaction = new Interaction(this.paper, this.pencil);
    this.interactionHolder = this.interaction;

    this._initColorPicker();
    this._initShapeGetter();
    this._bindDrawEvent();
    this._bindFillCanvasEvent();
    this._bindEraserEvent();
    this._bindResetPencilEvent();
    this._bindOpenColorPickerEvent();
    this._bindOpenShapeGetterEvent();
    this._bindColorPickerEvent();
    this._bindShapeGetterEvent();

  },

  paintPoint: function(point) {

    var pts = this.interaction.actWithPoint(point.x, point.y);
    for (var i = 0; i < pts.length; ++i) {
      this.canvas.fillStyle = pts[i].fillStyle;
      this.canvas.fillRect(pts[i].x, pts[i].y, 1, 1);
    }
  
  },

  paintPoints: function(points) {

    for (var i = 0; i < points.length; ++i) {
      this.paintPoint({
        x: points[i].x, 
        y: points[i].y
      });
    }

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

    canvas.mousedown(function(e) {
      is_down = true;

      var x = e.clientX - $(this).offset().left;
      var y = e.clientY - $(this).offset().top;

      x = Math.floor(x);
      y = Math.floor(y);

      _that.paintPoint({x:x, y:y});

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

        _that.paintPoint({x:x, y:y});
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
      $("#sidebar").hide();
    }

    resetButton.click(resetShapeGetterHandler);
    commitButton.click(commitShapeGetterHandler);

  },

  _bindColorPickerEvent: function() {

    var _that = this;
    var commitButton = $('#commitColor');

    var commitShapeGetterHandler = function() {
      _that.interaction.setColor(_that.colorPicker.color);
      $("#sidebar").hide();
    }

    commitButton.click(commitShapeGetterHandler);
 
  },

  _bindFillCanvasEvent: function() {
    var _that = this;
    var fillCanvasButton = $('#fill-canvas');

    var fillCanvasEventHandler = function() {
      _that.canvas_color = _that.interaction.getColor();
      _that.canvas.fillStyle = _that.canvas_color; 
      _that.canvas.fillRect(0,0,1500,500);
    }

    fillCanvasButton.click(fillCanvasEventHandler);
  },

  _bindEraserEvent: function() {
    var _that = this;
    var eraserButton = $('#eraser');
   
    var eraserEventHandler = function() {
      _that.interaction = new EraserInteraction(_that.paper, _that.pencil, _that.canvas_color);
      $("#color-picker").hide();
      $("#shape-getter").hide();
      $("#fill-canvas").hide();
      $("#reset-pencil").show();
    }

    eraserButton.click(eraserEventHandler);
  },

  _bindOpenColorPickerEvent: function() {
    var colorPickerButton = $('#color-picker');

    var openColorPickerEventHandler = function() {
      $("#pencil-shape").hide();
      $("#sidebar").show();
      $("#pencil-color").show();
    }

    colorPickerButton.click(openColorPickerEventHandler);
  },

  _bindOpenShapeGetterEvent: function() {
    var shapeGetterButton = $('#shape-getter');

    var openShapeGetterEventHandler = function() {
      $("#pencil-color").hide();
      $("#sidebar").show();
      $("#pencil-shape").show();
    }

    shapeGetterButton.click(openShapeGetterEventHandler);
  },

  _bindResetPencilEvent: function() {
    var _that = this;
    var resetPencilButton = $('#reset-pencil');

    var resetPencilEventHandler = function() {
      _that.interaction = _that.interactionHolder;
      $("#color-picker").show();
      $("#shape-getter").show();
      $("#fill-canvas").show();
      resetPencilButton.hide();
    }

    resetPencilButton.click(resetPencilEventHandler);
  },
}
