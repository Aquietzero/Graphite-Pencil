
function ColorPicker(dom_id, preview_id) {

  var dom = document.getElementById(dom_id);

  this.dom_id = dom_id;
  this.canvas = dom.getContext('2d');

  this.width  = dom.width;
  this.height = dom.height;

  this.color = { R:0, G:0, B:0 };

  var preview_dom = document.getElementById(preview_id);
  this.preview_id = preview_id;
  this.preview = preview_dom.getContext('2d');

  this.preview_width  = preview_dom.width;
  this.preview_height = preview_dom.height;

}


ColorPicker.prototype = {

  init: function() {

    var _that = this;

    // Load colors.
    this._loadColors('img/hv.png', function() {
      _that.canvas.drawImage(this, 0, 0, _that.width, _that.height);
    });

    this._bindPickColorEvent();
  
  },

  _loadColors: function(src, callback) {
  
    var colors = new Image();
    colors.src = src;

    if (colors.complete) {
      callback.call(colors);
      return;
    }

    colors.onload = function() {
      callback.call(colors);
    }

  }, 

  _bindPickColorEvent: function() {

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


        var imageData = _that.canvas.getImageData(0, 0, _that.width, _that.height);
        var data = imageData.data;

        var red   = data[((_that.width * y) + x) * 4];
        var green = data[((_that.width * y) + x) * 4 + 1];
        var blue  = data[((_that.width * y) + x) * 4 + 2];
        _that.color = { R:red, G:green, B:blue };

        _that.preview.fillStyle = _that._colorToString();
        _that.preview.fillRect(0, 0, _that.preview_width, _that.preview_height);
      }
    });

  },

  _colorToString: function() {
    return 'rgb(' + this.color.R + ',' + this.color.G + ',' + this.color.B + ')';
  }

}
