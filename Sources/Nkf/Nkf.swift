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

public enum Nkf {
    @NkfActor public static func convert(_ string: String, encoding: Encoding) -> Data? {
        let options = "-m0 --ic=UTF-8 --oc=\(encoding)"

        var resultSize: Int32 = 0
        let resultBuf = options.withCString { optionsPtr in
            var inputBuf = Array(string.utf8)
            return nkf_convert(
                &inputBuf,
                Int32(inputBuf.count),
                UnsafeMutableRawPointer(mutating: optionsPtr),
                &resultSize
            )
        }

        if let resultBuf {
            return Data(bytes: resultBuf, count: Int(resultSize))
        }
        return nil
    }
}
