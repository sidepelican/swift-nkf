import Testing
import Nkf

#if os(macOS)
let isApplePlatform = true
#else
let isApplePlatform = false
#endif

@Test(
    .enabled(if: isApplePlatform),
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
func stringToShiftJIS(_ string: String) async throws {
    let encoded = try #require(await Nkf.convert(string, encoding: .shiftJIS))
    let decoded = String(data: encoded, encoding: .shiftJIS)
    #expect(decoded == string)
}
