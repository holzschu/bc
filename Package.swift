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
            checksum: "b1696873822a66697ef2cb7bfcf84cad539daf7e7da9f77a91f6759f75c4892b"
        )
    ]
)
