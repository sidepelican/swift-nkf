# Swift Nkf

nkf (Network Kanji Filter) binding for Swift.

# Getting Started

## Adding the dependency

To add a dependency on the package, declare it in your `Package.swift`:

```swift
.package(url: "https://github.com/sidepelican/swift-nkf.git", from: "0.1.0"),
```

and to your application target, add `Nkf` to your dependencies:

```swift
.product(name: "Nkf", package: "swift-nkf"),
```

# Usage

## `String` to `Data`

```swift
import Nkf

let data = await Nkf.data("こんにちは", encoding: .shiftJIS)
```

## `Data` to `String`

```swift
import Nkf

let string = await Nkf.string(data, encoding: .shiftJIS)
```
