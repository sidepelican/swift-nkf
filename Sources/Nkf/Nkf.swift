import Foundation
import CNkf

public enum Encoding: Character {
    case iso2022JP = "j"
    case shiftJIS = "s"
    case eucJP = "e"
    case utf8 = "w"
}

public enum Nkf {
    @NkfActor public static func convert(_ string: String, encoding: Encoding) -> Data? {
        let options = "-m0 --ic=UTF-8 --oc=Windows-31J"

        let result = nkf_convert(
            input: UInt8Vector(string.utf8),
            options: std.string(options)
        )

        return Data(result)
    }
}
