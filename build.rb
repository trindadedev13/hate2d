require 'fileutils'

def run(*cmd)
   puts *cmd
   system(*cmd) or abort("Failed #{cmd.join('')}")
end

option_termux = false
option_run = false
option_asan = false

ARGV.each do |arg|
  case arg
    when "--termux", "-t"
      option_termux = true
    when "--run", "-r"
      option_run = true
    when "--asan", "-as"
      option_asan = true
  end
end

FileUtils.mkdir_p("build")

install_pr = ENV["PREFIX"]
run(
    "cmake -B build -S . " \
    "-DASAN=#{option_asan ? "ON" : "OFF"} " \
    "-DCMAKE_INSTALL_PREFIX=#{install_pr} "
)
run("cmake --build build")

if option_run
  if not option_termux
    run("chmod +x build/hate2d")
    run("./build/hate2d")
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
  
    system(exec_path)
    cleanup(x11_pid)
  end
end