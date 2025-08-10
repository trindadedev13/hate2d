w = 0
h = 0
function hate2d.load()
  w, h = hate2d.window.get_dimensions()
end

function hate2d.draw()
  hate2d.graphics.clear(hate2d.color.BLACK)

  local startX = w / 2
  local startY = 50
  local spacing = 40

  -- hello world text
  hate2d.graphics.draw_text("Hello, world!", startX, startY, hate2d.color.WHITE)
  startY = startY + spacing

  -- outlined rect
  -- you can just use "outlined" instead the const
  hate2d.graphics.draw_rect(hate2d.graphics.STYLE_OUTLINED, {10, startY, 200, 200}, hate2d.color.RED)
  startY = startY + 200 + 10

  -- filled rect
  -- you can just use "filled" instead the const
  hate2d.graphics.draw_rect(hate2d.graphics.STYLE_FILLED, {10, startY, 200, 200}, hate2d.color.GREEN)
  startY = startY + 200 + 10

  -- red pixels
  for i = 1, 10 do
    hate2d.graphics.draw_pixel(20 + i, startY, hate2d.color.RED)
  end
  startY = startY + 20

  -- circle outlined
  -- you can just use "outlined" instead the const
  hate2d.graphics.draw_circle(hate2d.graphics.STYLE_OUTLINED, 200, startY + 100, 100, hate2d.color.BLUE)
  startY = startY + 200 + 10

  -- circle filled
  -- you can just use "filled" instead the const
  hate2d.graphics.draw_circle(hate2d.graphics.STYLE_FILLED, 400, startY + 100, 100, hate2d.color.WHITE)
  startY = startY + 200 + 10

  -- image
  local img = hate2d.Image.new("background.png", 500, startY + 100, 300, 300)
  hate2d.graphics.draw_image(img)
end