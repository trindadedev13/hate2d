require "fileutils"

def run(*cmd)
   puts *cmd
   system(*cmd) or abort("Failed #{cmd.join('')}")
end

def help()
  puts "hate2d buildscript"
  puts
  puts "--build   or -b:  Compiles"
  puts "--run     or -r:  Compiles and run executables."
  puts "--install or -i:  Compiles and installs executable."
  puts "--termux  or -t:  Compiles the executable fixing termux problems."
  puts "--asan    or -as: Compiles with Address Sanitizer Enable."
  puts "--gdb     or -g:  If used with --run, will run with GNU Debugger, use this to debugging."
  puts "--help    or -h:  Shows help."
end

option_build = false
option_termux = false
option_run = false
option_asan = false
option_gdb = false
option_install = false

ARGV.each do |arg|
  case arg
    when "--build", "-b"
      option_build = true
    when "--termux", "-t"
      option_termux = true
    when "--run", "-r"
      option_run = true
    when "--asan", "-as"
      option_asan = true
    when "--gdb", "-g"
      option_gdb = true
    when "--install", "-i"
      option_install = true
    when "--help", "-h"
      help
      exit 1
    else
      puts "Arg #{arg} is not a valid command."
      puts "use --help to see all commands"
      exit 1
  end
end

if option_build
  FileUtils.mkdir_p("build")

  install_pr = ENV["PREFIX"]
  run(
      "cmake -B build -S . " \
      "-DASAN=#{option_asan ? "ON" : "OFF"} " \
      "-DCMAKE_INSTALL_PREFIX=#{install_pr} "
  )
  run("cmake --build build")
end

if option_install
  run("cmake --install build")
end

if option_run
  args = [ "test" ].join(" ")

  if not option_termux
    run("chmod +x build/hate2d #{args}")
    if option_gdb
      run("gdb ./build/hate2d --args ./build/hate2d #{args}")
    else
      run("./build/hate2d #{args}")
    end
  else
    HOME = ENV["HOME"]
    ENV["DISPLAY"] = ":0"

    FileUtils.mkdir_p("#{HOME}/temp/c/hate2d/")
    FileUtils.cp("build/hate2d", "#{HOME}/temp/c/hate2d/hate2d")
    
    EXECUTABLE = "hate2d"
    x11_pid = spawn("termux-x11 :0")
    
    def cleanup(x11_pid)
      puts "Shutting down termux-x11..."
      Process.kill("TERM", x11_pid)
      exit
    end
    
    Signal.trap("INT") do
      cleanup(x11_pid)
    end
    
    sleep 5
    
    exec_path = File.expand_path("~/temp/c/hate2d/#{EXECUTABLE}")
    File.chmod(0755, exec_path)
  
    if option_gdb
      system("gdb #{exec_path} --args #{exec_path} #{args}")
    else
      system("#{exec_path} #{args}")
    end
    cleanup(x11_pid)
  end
end