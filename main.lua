w = 0
h = 0
function hate2d.load()
  -- onCreate
  w, h = hate2d.window.get_dimensions()
end

function hate2d.draw()
  hate2d.graphics.print("Hello, world!", w / 2, h / 2)
  hate2d.graphics.print("Who!", w / 2, h / 2)
end