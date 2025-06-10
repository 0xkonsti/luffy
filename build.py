import os
import subprocess
import argparse
import shutil

def run_command(cmd):
    print(">>>", " ".join(cmd))
    subprocess.run(cmd, check=True)


def main():
    parser = argparse.ArgumentParser(description="CMake Build Helper")
    parser.add_argument("--clean", action="store_true", help="Löscht den build-Ordner")
    parser.add_argument("--graphics", action="store_true", help="Aktiviere Grafikmodule (GLFW/GLAD)")
    parser.add_argument("--shared", action="store_true", help="Baue als Shared Library")
    parser.add_argument("--static", action="store_true", help="Baue als Static Library")
    parser.add_argument("--build-dir", default="build", help="Build-Verzeichnis")
    parser.add_argument("--install", action="store_true", help="Führe Installation nach Build durch")
    parser.add_argument("--test", action="store_true", help="Führe nach dem Build alle Tests mit ctest aus")
    parser.add_argument("--config", default="Debug", help="Build-Konfiguration für CTest (nur MSVC)")
    args = parser.parse_args()

    build_dir = args.build_dir

    if args.clean and os.path.exists(build_dir):
        print(f">>> Lösche {build_dir}/")
        shutil.rmtree(build_dir)

    cmake_config = [
        "cmake",
        "-B", build_dir,
        "-DLUFFY_ENABLE_GRAPHICS={}".format("ON" if args.graphics else "OFF"),
        "-DBUILD_SHARED_LIBS={}".format("ON" if args.shared else "OFF"),
    ]

    print(">>> Konfiguriere Projekt...")
    run_command(cmake_config)

    print(">>> Baue Projekt...")
    run_command(["cmake", "--build", build_dir])

    if args.install:
        print(">>> Installiere Projekt...")
        run_command(["cmake", "--install", build_dir])
        
    if args.test:
        print(">>> Führe Tests aus...")
        cmd = ["ctest", "--test-dir", build_dir, "--output-on-failure"]
        if os.name == "nt":
            cmd += ["-C", args.config]
        run_command(cmd)

if __name__ == "__main__":
    main()