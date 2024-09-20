import Testing
import Nkf

#if os(macOS)
let isApplePlatform = true
#else
let isApplePlatform = false
#endif

@Test(
    arguments: [
        "Hello, World",
        "こんにちは",
        """
        メールアドレス,氏名,パスワード,種別(区分),確認機能(0:なし、1:あり)
        foo@example.com,foo,password,"001,002",0
        bar@example.com,bar,password,"002,003",1
        """,
    ]
)
func shiftJIS(_ string: String) async throws {
    let encoded = try #require(await Nkf.data(string, encoding: .shiftJIS))
    if isApplePlatform {
        let cfEncoded = try #require(string.data(using: .shiftJIS))
        #expect(cfEncoded == encoded)

        let cfDecoded = String(data: encoded, encoding: .shiftJIS)
        #expect(cfDecoded == string)
    }
    let decoded = try #require(await Nkf.string(encoded, encoding: .shiftJIS))
    #expect(decoded == string)
}
