w = 0
h = 0
function hate2d.load()
  w, h = hate2d.window.get_dimensions()
end

function hate2d.draw()
  hate2d.graphics.clear(hate2d.color.BLACK)
  hate2d.graphics.draw_text("Hello, world!", w / 2, h / 2, hate2d.color.WHITE)
  local myrect = {10, 10, 200, 200}
  hate2d.graphics.fill_rect(myrect, hate2d.color.WHITE)

  for i = 1, 10 do
    hate2d.graphics.draw_pixel(20+i, 300, hate2d.color.RED)
  end
end