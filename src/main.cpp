namespace
{
	void MessageHandler(OBSE::MessagingInterface::Message* a_msg)
	{
		switch (a_msg->type)
		{
		case OBSE::MessagingInterface::kPostLoad:
			REX::INFO("PostLoad");
			break;
		case OBSE::MessagingInterface::kPostPostLoad:
			REX::INFO("PostPostLoad");
			break;
		default:
			break;
		}
	}
}

OBSE_PLUGIN_PRELOAD(const OBSE::PreLoadInterface* a_obse)
{
	OBSE::Init(a_obse);
	REX::INFO("Preload");
	return true;
}

OBSE_PLUGIN_LOAD(const OBSE::LoadInterface* a_obse)
{
	OBSE::Init(a_obse);
	OBSE::GetMessagingInterface()->RegisterListener(MessageHandler);
	REX::INFO("Load");
	return true;
}
