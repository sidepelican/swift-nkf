// nkf is not thread-safe, so it can only be operated from one thread.
@globalActor public actor NkfActor: GlobalActor {
    public static let shared = NkfActor()
}
