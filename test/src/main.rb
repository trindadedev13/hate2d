$w = 0
$h = 0

def load()
  $w, $h = Hate2D::Window.get_dimensions
end

def draw()
  Hate2D::Graphics.clear(Hate2D::Color::BLACK)

  start_x = $w / 2
  start_y = 50
  spacing = 40

  Hate2D::Graphics.draw_text("Hello, world!", start_x, start_y, Hate2D::Color::WHITE, Hate2D::Font::DEFAULT_FONT)
  start_y += spacing

  minecraft_font = Hate2D::Font.load("minecraft_regular.ttf", 35)
  Hate2D::Graphics.draw_text("Minecraft", start_x, start_y, Hate2D::Color::WHITE, minecraft_font)
  start_y += spacing

  Hate2D::Graphics.draw_rect(Hate2D::Graphics::STYLE_OUTLINED, [10, start_y, 200, 200], Hate2D::Color::RED)
  start_y += 200 + 10

  Hate2D::Graphics.draw_rect(Hate2D::Graphics::STYLE_FILLED, [10, start_y, 200, 200], Hate2D::Color::GREEN)
  start_y += 200 + 10

  1.upto(10) do |i|
    Hate2D::Graphics.draw_pixel(20 + i, start_y, Hate2D::Color::RED)
  end
  start_y += 20

  Hate2D::Graphics.draw_circle(Hate2D::Graphics::STYLE_OUTLINED, 200, start_y + 100, 200, Hate2D::Color::BLUE)
  start_y += 200 + 10

  Hate2D::Graphics.draw_circle(Hate2D::Graphics::STYLE_FILLED, 400, start_y + 100, 200, Hate2D::Color::WHITE)
  start_y += 200 + 10

  img = Hate2D::Image.load("background.png", 500, start_y + 100, 300, 300)
  Hate2D::Graphics.draw_image(img)
end