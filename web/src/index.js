$(function() {

  var ctx = document.getElementById('pencil-canvas').getContext('2d');
  var is_down = false;

  var elems = [];

  elems.push(new Elem( 0,  5, 0.5, 0.5));
  elems.push(new Elem( 2,  2, 0.5, 0.5));
  elems.push(new Elem( 2, -2, 0.5, 0.5));
  elems.push(new Elem( 0, -5, 0.5, 0.5));
  elems.push(new Elem(-2, -2, 0.5, 0.5));
  elems.push(new Elem(-2,  2, 0.5, 0.5));

  var paper = new Paper(800, 500, 2000, 0.5, 0.5);

  /*
  var grey;
  for (var i = 0; i < paper.width; ++i) {
    for (var j = 0; j < paper.height; ++j) {
      grey = paper.grains[i][j].h * 255;
      ctx.fillStyle = 'rgb(' + 
        Math.floor(grey) + ',' +
        Math.floor(grey) + ',' +
        Math.floor(grey) + ')';
      ctx.fillRect(i, j, 1, 1);
    }
  }
  */

  var pencil = new Pencil(0.5, 0.5, 0.4, 0.5, 0.05, elems);
  pencil.getPoints();

  var interaction = new Interaction(paper, pencil);

  $('#pencil-canvas').mousedown(function() {
    is_down = true;
  });

  $('#pencil-canvas').mouseup(function() {
    is_down = false;
  });

  $('#pencil-canvas').mousemove(function(e) {

    if (is_down) {
      var x = e.clientX - $(this).offset().left;
      var y = e.clientY - $(this).offset().top;
      // console.log(x + '---' + y);
      // put_pixel(ctx, x, y);
      interaction.act(x, y, ctx);
    }

  });

})

function put_pixel(canvas, x, y) {

  canvas.fileStyle = '#000000';
  canvas.fillRect(x, y, 1, 1);

}
