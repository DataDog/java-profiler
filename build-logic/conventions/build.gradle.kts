plugins {
    `kotlin-dsl`
}

repositories {
    gradlePluginPortal()
    mavenCentral()
}

dependencies {
    implementation("org.jetbrains.kotlin:kotlin-stdlib")
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
    }
}
