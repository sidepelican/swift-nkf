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
            dependencies: ["CNkf"],
            swiftSettings: [
                .interoperabilityMode(.Cxx),
            ]
        ),
        .testTarget(
            name: "NkfTests",
            dependencies: ["Nkf"],
            swiftSettings: [
                .interoperabilityMode(.Cxx),
            ]
        ),
        .target(
            name: "CNkf",
            path: ".",
            sources: [
                "Sources/CNkf",
            ],
            publicHeadersPath: "Sources/CNkf/include",
            cxxSettings: [
                .headerSearchPath("nkf"),
            ]
        )
    ],
    swiftLanguageModes: [.v6],
    cxxLanguageStandard: .cxx20
)
