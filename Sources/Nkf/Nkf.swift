import Foundation
private import CNkf

public struct Encoding: CustomStringConvertible, Sendable {
    public var description: String

    public static let iso2022JP = Encoding(description: "ISO-2022-JP")
    public static let shiftJIS = Encoding(description: "Shift_JIS")
    public static let cp932 = Encoding(description: "Windows-31J")
    public static let eucJP = Encoding(description: "EUC-JP")
    public static let utf8 = Encoding(description: "UTF-8")
}

@NkfActor public enum Nkf {
    public static func data(_ string: String, encoding: Encoding) -> Data {
        let options = "--ic=UTF-8 --oc=\(encoding)"

        return Array(string.utf8).withUnsafeBytes {
            convert($0, options: options)
        }
    }

    public static func string(_ data: Data, encoding: Encoding) -> String {
        let options = "--ic=\(encoding) --oc=UTF-8"

        let result = data.withUnsafeBytes {
            convert($0, options: options)
        }
        return String(data: result, encoding: .utf8) ?? ""
    }

    public static func convert(_ data: Data, options: String) -> Data {
        return data.withUnsafeBytes {
            convert($0, options: options)
        }
    }

    private static func convert(_ data: UnsafeRawBufferPointer, options: String) -> Data {
        var resultSize: Int32 = 0
        let resultBuf = options.withCString { optionsPtr in
            nkf_convert(
                data.baseAddress,
                Int32(data.count),
                UnsafeMutableRawPointer(mutating: optionsPtr),
                &resultSize
            )
        }

        guard let resultBuf else {
            assertionFailure("never happen")
            return Data()
        }
        return Data(bytes: resultBuf, count: Int(resultSize))
    }
}
