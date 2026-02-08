import java.net.URI

buildscript {
  dependencies {
    classpath("com.dipien:semantic-version-gradle-plugin:2.0.0")
  }
  repositories {
    mavenLocal()
    mavenCentral()
    gradlePluginPortal()
  }
}

plugins {
  id("io.github.gradle-nexus.publish-plugin") version "2.0.0"
  id("com.datadoghq.native-root")
}

version = "1.38.0"

apply(plugin = "com.dipien.semantic-version")
version = findProperty("ddprof_version") as? String ?: version

allprojects {
  repositories {
    mavenCentral()
    gradlePluginPortal()
  }
}

repositories {
  mavenLocal()
  mavenCentral()
  gradlePluginPortal()

  maven {
    content {
      includeGroup("com.datadoghq")
    }
    mavenContent {
      snapshotsOnly()
    }
    // see https://central.sonatype.org/publish/publish-portal-snapshots/#consuming-via-gradle
    url = URI("https://central.sonatype.com/repository/maven-snapshots/")
  }
}

allprojects {
  group = "com.datadoghq"

  // Apply spotless formatting convention to all projects
  apply(plugin = "com.datadoghq.spotless-convention")
}

subprojects {
  version = rootProject.version
}

val isCI = hasProperty("CI") || System.getenv("CI")?.toBoolean() ?: false

nexusPublishing {
  repositories {
    val forceLocal = hasProperty("forceLocal")

    if (forceLocal && !isCI) {
      create("local") {
        // For testing use with https://hub.docker.com/r/sonatype/nexus
        // docker run --rm -d -p 8081:8081 --name nexus sonatype/nexus
        // Doesn't work for testing releases though... (due to staging)
        nexusUrl.set(URI("http://localhost:8081/nexus/content/repositories/releases/"))
        snapshotRepositoryUrl.set(URI("http://localhost:8081/nexus/content/repositories/snapshots/"))
        username.set("admin")
        password.set("admin123")
      }
    } else {
      // see https://github.com/gradle-nexus/publish-plugin#publishing-to-maven-central-via-sonatype-central
      // For official documentation:
      // staging repo publishing https://central.sonatype.org/publish/publish-portal-ossrh-staging-api/#configuration
      // snapshot publishing https://central.sonatype.org/publish/publish-portal-snapshots/#publishing-via-other-methods
      create("sonatype") {
        // see https://central.sonatype.org/publish/publish-portal-ossrh-staging-api/#configuration
        // see https://github.com/gradle-nexus/publish-plugin#publishing-to-maven-central-via-sonatype-central
        // Also for official doc
        // staging repo publishing https://central.sonatype.org/publish/publish-portal-ossrh-staging-api/#configuration
        // snapshot publishing https://central.sonatype.org/publish/publish-portal-snapshots/#publishing-via-other-methods
        nexusUrl.set(URI("https://ossrh-staging-api.central.sonatype.com/service/local/"))
        snapshotRepositoryUrl.set(URI("https://central.sonatype.com/repository/maven-snapshots/"))

        username.set(System.getenv("SONATYPE_USERNAME"))
        password.set(System.getenv("SONATYPE_PASSWORD"))
      }
    }
  }
}
