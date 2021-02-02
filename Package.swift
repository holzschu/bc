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
            url: "https://github.com/holzschu/bc/releases/download/v1.0/bc_ios.xcframework.zip",
            checksum: "e3d72c562f726614e273efb06f6e63ccd23f9e38b14c468cf9febd4302df5fdd"
        )
    ]
)
