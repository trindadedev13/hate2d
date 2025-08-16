.. _hate2d_example:

==========================
Hate2D Example Documentation
==========================

This document provides a detailed description of each **Hate2D framework function** used in the provided example script.

.. contents:: Table of Contents
   :depth: 2

Global Variables
================

.. code-block:: ruby

   $w = 0    
   $h = 0

- **$w**: Stores the width of the window.
- **$h**: Stores the height of the window.

Framework Functions
===================

Hate2D::Window.get_dimensions
-----------------------------

.. code-block:: ruby

   $w, $h = Hate2D::Window.get_dimensions

- **Description**: Returns the current window width and height.
- **Parameters**: None
- **Returns**: `[width, height]` (integers)
- **Usage**:

  .. code-block:: ruby

     w, h = Hate2D::Window.get_dimensions


Hate2D::Graphics.clear(color)
-----------------------------

.. code-block:: ruby

   Hate2D::Graphics.clear(Hate2D::Color::BLACK)

- **Description**: Clears the screen with the specified color.
- **Parameters**:
  - `color`: A `Hate2D::Color` constant.
- **Returns**: None
- **Usage**:

  .. code-block:: ruby

     Hate2D::Graphics.clear(Hate2D::Color::WHITE)


Hate2D::Graphics.draw_text(text, x, y, color, font)
--------------------------------------------------

.. code-block:: ruby

   Hate2D::Graphics.draw_text("Hello, world!", 100, 50, Hate2D::Color::WHITE, Hate2D::Font::DEFAULT_FONT)

- **Description**: Draws text on the screen.
- **Parameters**:
  - `text`: String to be displayed.
  - `x, y`: Screen coordinates.
  - `color`: Text color.
  - `font`: Font object.
- **Returns**: None
- **Usage**:

  .. code-block:: ruby

     font = Hate2D::Font.load("arial.ttf", 20)
     Hate2D::Graphics.draw_text("Score: 100", 20, 20, Hate2D::Color::GREEN, font)


Hate2D::Font.load(path, size)
-----------------------------

.. code-block:: ruby

   minecraft_font = Hate2D::Font.load("minecraft_regular.ttf", 35)

- **Description**: Loads a font from file with a given size.
- **Parameters**:
  - `path`: Path to the `.ttf` font file.
  - `size`: Font size.
- **Returns**: Font object.
- **Usage**:

  .. code-block:: ruby

     font = Hate2D::Font.load("arial.ttf", 24)


Hate2D::Graphics.draw_rect(style, [x, y, w, h], color)
------------------------------------------------------

.. code-block:: ruby

   Hate2D::Graphics.draw_rect(Hate2D::Graphics::STYLE_OUTLINED, [10, 100, 200, 200], Hate2D::Color::RED)

- **Description**: Draws a rectangle.
- **Parameters**:
  - `style`: `STYLE_OUTLINED` or `STYLE_FILLED`.
  - `[x, y, w, h]`: Position and dimensions.
  - `color`: Fill or outline color.
- **Returns**: None
- **Usage**:

  .. code-block:: ruby

     Hate2D::Graphics.draw_rect(Hate2D::Graphics::STYLE_FILLED, [50, 50, 100, 150], Hate2D::Color::BLUE)


Hate2D::Graphics.draw_pixel(x, y, color)
---------------------------------------

.. code-block:: ruby

   Hate2D::Graphics.draw_pixel(20, 300, Hate2D::Color::RED)

- **Description**: Draws a single pixel at the given coordinates.
- **Parameters**:
  - `x, y`: Screen coordinates.
  - `color`: Pixel color.
- **Returns**: None
- **Usage**:

  .. code-block:: ruby

     Hate2D::Graphics.draw_pixel(100, 200, Hate2D::Color::WHITE)


Hate2D::Graphics.draw_circle(style, x, y, radius, color)
-------------------------------------------------------

.. code-block:: ruby

   Hate2D::Graphics.draw_circle(Hate2D::Graphics::STYLE_FILLED, 200, 200, 100, Hate2D::Color::GREEN)

- **Description**: Draws a circle.
- **Parameters**:
  - `style`: `STYLE_OUTLINED` or `STYLE_FILLED`.
  - `x, y`: Center of the circle.
  - `radius`: Circle radius.
  - `color`: Circle color.
- **Returns**: None
- **Usage**:

  .. code-block:: ruby

     Hate2D::Graphics.draw_circle(Hate2D::Graphics::STYLE_OUTLINED, 400, 300, 50, Hate2D::Color::BLUE)


Hate2D::Image.load(path, x, y, w, h)
-----------------------------------

.. code-block:: ruby

   img = Hate2D::Image.load("background.png", 500, 200, 300, 300)

- **Description**: Loads an image and prepares it for rendering.
- **Parameters**:
  - `path`: Path to the image file.
  - `x, y`: Position where the image will be drawn.
  - `w, h`: Image width and height.
- **Returns**: Image object.
- **Usage**:

  .. code-block:: ruby

     logo = Hate2D::Image.load("logo.png", 50, 50, 128, 128)


Hate2D::Graphics.draw_image(image)
---------------------------------

.. code-block:: ruby

   Hate2D::Graphics.draw_image(img)

- **Description**: Renders an image previously loaded with `Hate2D::Image.load`.
- **Parameters**:
  - `image`: Image object.
- **Returns**: None
- **Usage**:

  .. code-block:: ruby

     bg = Hate2D::Image.load("bg.png", 0, 0, 800, 600)
     Hate2D::Graphics.draw_image(bg)