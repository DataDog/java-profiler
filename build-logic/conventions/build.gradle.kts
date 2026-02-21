plugins {
    `kotlin-dsl`
}

repositories {
    gradlePluginPortal()
    mavenCentral()
}

dependencies {
    implementation("org.jetbrains.kotlin:kotlin-stdlib")
    implementation("com.diffplug.spotless:spotless-plugin-gradle:8.2.1")
}

gradlePlugin {
    plugins {
        create("nativeBuild") {
            id = "com.datadoghq.native-build"
            implementationClass = "com.datadoghq.native.NativeBuildPlugin"
        }
        create("nativeRoot") {
            id = "com.datadoghq.native-root"
            implementationClass = "com.datadoghq.native.RootProjectPlugin"
        }
        create("gtest") {
            id = "com.datadoghq.gtest"
            implementationClass = "com.datadoghq.native.gtest.GtestPlugin"
        }
        create("scanbuild") {
            id = "com.datadoghq.scanbuild"
            implementationClass = "com.datadoghq.native.scanbuild.ScanBuildPlugin"
        }
        create("profilerTest") {
            id = "com.datadoghq.profiler-test"
            implementationClass = "com.datadoghq.profiler.ProfilerTestPlugin"
        }
        create("spotlessConvention") {
            id = "com.datadoghq.spotless-convention"
            implementationClass = "com.datadoghq.profiler.SpotlessConventionPlugin"
        }
        create("javaConventions") {
            id = "com.datadoghq.java-conventions"
            implementationClass = "com.datadoghq.profiler.JavaConventionsPlugin"
        }
        create("fuzzTargets") {
            id = "com.datadoghq.fuzz-targets"
            implementationClass = "com.datadoghq.native.fuzz.FuzzTargetsPlugin"
        }
        create("simpleNativeLib") {
            id = "com.datadoghq.simple-native-lib"
            implementationClass = "com.datadoghq.native.SimpleNativeLibPlugin"
        }
        create("versionedSources") {
            id = "com.datadoghq.versioned-sources"
            implementationClass = "com.datadoghq.java.versionedsources.VersionedSourcesPlugin"
        }
    }
}
