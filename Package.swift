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
            checksum: "535181787b8bb7aad3f009b5568394bc386c81a58a280f679eaeaeca3a3ad389"
        )
    ]
)
