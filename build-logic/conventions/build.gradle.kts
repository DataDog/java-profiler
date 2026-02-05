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
    }
}
