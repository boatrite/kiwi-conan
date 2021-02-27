from conans import ConanFile, CMake, tools


# Kiwi (https://github.com/nucleic/kiwi) is a header only library which makes
# it very easy to integrate with Conan.
class KiwiConanConan(ConanFile):
    name = "kiwi-conan"
    version = "0.1"
    no_copy_source = True

    def source(self):
        self.run("git clone https://github.com/nucleic/kiwi")

    def package(self):
        self.copy("*.h", dst="include", src="kiwi/kiwi")
