import Foundation
private import CNkf

public enum Encoding: Character {
    case iso2022JP = "j"
    case shiftJIS = "s"
    case eucJP = "e"
    case utf8 = "w"
}

public enum Nkf {
    @NkfActor public static func convert(_ string: String, encoding: Encoding) -> Data? {
        let options = "-m0 --ic=UTF-8 --oc=Windows-31J"

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
