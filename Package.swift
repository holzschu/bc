// swift-tools-version:5.3

import PackageDescription

let package = Package(
    name: "bc_ios",
    products: [
        .library(name: "bc_ios", targets: ["bc_ios"])
    ],
    dependencies: [
    ],
    targets: [
        .binaryTarget(
            name: "bc_ios",
            url: "https://github.com/holzschu/bc/releases/download/1.0/bc_ios.xcframework.zip",
            checksum: "50f78d889b6915aa3793df9823f2bf07697834e81b5245492bd038b118f50ec8"
        )
    ]
)
