// swift-tools-version: 6.0

import PackageDescription

let package = Package(
    name: "swift-nkf",
    products: [
        .library(name: "Nkf", targets: ["Nkf"]),
    ],
    targets: [
        .target(
            name: "Nkf",
            dependencies: ["CNkf"]
        ),
        .testTarget(
            name: "NkfTests",
            dependencies: ["Nkf"]
        ),
        .target(
            name: "CNkf",
            path: ".",
            sources: [
                "Sources/CNkf",
            ],
            publicHeadersPath: "Sources/CNkf/include",
            cSettings: [
                .headerSearchPath("nkf"),
            ]
        )
    ],
    swiftLanguageModes: [.v6],
    cxxLanguageStandard: .cxx20
)
