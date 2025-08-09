w = 0
h = 0
function hate2d.load()
  -- onCreate
  w, h = hate2d.window.get_dimensions()
  -- for k,v in pairs(hate2d.color) do
    -- print(k, v[1], v[2], v[3], v[4])
  -- end
end

function hate2d.draw()
  hate2d.graphics.clear(hate2d.color.BLACK)
  hate2d.graphics.draw_text("Hello, world!", w / 2, h / 2, hate2d.color.WHITE)
  local myrect = {10, 10, 200, 200}
  hate2d.graphics.fill_rect(myrect, hate2d.color.WHITE)
end