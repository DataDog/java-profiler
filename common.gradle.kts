import org.gradle.internal.os.OperatingSystem
import java.nio.charset.Charset
import java.nio.file.Files
import java.nio.file.Paths

buildscript {
  repositories {
    mavenLocal()
    mavenCentral()
    gradlePluginPortal()
  }
}

fun os(): OperatingSystem {
  return OperatingSystem.current()
}

fun osIdentifier(): String {
  return when {
    os().isMacOsX -> "macos"
    os().isLinux -> "linux"
    else -> throw RuntimeException("Unknown OS: ${os()}")
  }
}

fun arch(): String {
  return System.getProperty("os.arch")
}

fun archIdentifier(): String {
  val reportedArch = System.getProperty("os.arch")
  return when (reportedArch) {
    "x86_64", "amd64", "k8" -> "x64"
    "x86", "i386", "i486", "i586", "i686" -> "x86"
    "ARM", "aarch32" -> "arm"
    "arm64", "aarch64" -> "arm64"
    else -> throw RuntimeException("Unknown arch type: $reportedArch")
  }
}

fun javaHome(): String {
  return System.getenv("JAVA_HOME") ?: System.getProperty("java.home")
}

fun containsArray(container: ByteArray, offset: Int, contained: ByteArray): Boolean {
  for (i in contained.indices) {
    val leftPos = offset + i
    if (leftPos >= container.size) {
      return false
    }
    if (container[leftPos] != contained[i]) {
      return false
    }
  }
  return true
}

/**
 * There is information about the linking in the ELF file. Since properly parsing ELF is not
 * trivial this code will attempt a brute-force approach and will scan the first 4096 bytes
 * of the 'java' program image for anything prefixed with `/ld-` - in practice this will contain
 * `/ld-musl` for musl systems and probably something else for non-musl systems (eg. `/ld-linux-...`).
 * However, if such string is missing should indicate that the system is not a musl one.
 */
fun isMusl(): Boolean {
  val magic = byteArrayOf(127, 69, 76, 70) // *ELF
  val prefix = "/ld-".toByteArray(Charset.defaultCharset()) // '/ld-*'
  val musl = "musl".toByteArray(Charset.defaultCharset()) // 'musl'

  val binary = Paths.get(javaHome(), "bin", "java")
  val buffer = ByteArray(4096)

  Files.newInputStream(binary).use { inputStream ->
    var read = inputStream.read(buffer, 0, 4)
    if (read != 4 || !containsArray(buffer, 0, magic)) {
      return false
    }
    read = inputStream.read(buffer)
    if (read <= 0) {
      return false
    }
    var prefixPos = 0
    for (i in 0 until read) {
      if (buffer[i] == prefix[prefixPos]) {
        if (++prefixPos == prefix.size) {
          return containsArray(buffer, i + 1, musl)
        }
      } else {
        prefixPos = 0
      }
    }
  }
  return false
}

val hasGtestProperty = "hasGtest"

// Define potential GTest locations for MacOS and Linux
val gtestLocations = mapOf(
  "macos" to listOf("/opt/homebrew/opt/googletest", "/usr/local/opt/googletest"),
  "linux" to listOf("/usr/include/gtest", "/usr/local/include/gtest")
)

// Function to check if any of the specified paths exist
fun checkGtestPaths(paths: List<String>): Boolean {
  return paths.any { file(it).exists() }
}

// Determine OS and check for GTest
val hasGtest = when {
  os().isMacOsX -> checkGtestPaths(gtestLocations["macos"]!!)
  os().isLinux -> checkGtestPaths(gtestLocations["linux"]!!)
  else -> false
}

// Log a message for debugging
if (!hasGtest) {
  println("GTest not found. Please install GTest or configure paths.")
}

// Export functions and properties to extra
extra["isMusl"] = ::isMusl
extra["os"] = ::os
extra["osIdentifier"] = ::osIdentifier
extra["arch"] = ::arch
extra["archIdentifier"] = ::archIdentifier
extra["javaHome"] = ::javaHome
extra["hasGtest"] = hasGtest
