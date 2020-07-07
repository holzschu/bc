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
            checksum: "f32a68b335fef4007272da0d7a301b8fc9f2ef3c895c242a4f055f1665b0837d"
        )
    ]
)
