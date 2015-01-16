#ifndef SKYPE_H
#define SKYPE_H

#include <QAxObject>
#include <QDebug>


enum TApiSecurityContext
{
    apiContextUnknown	=0,
    apiContextVoice	=1,
    apiContextMessaging	=2,
    apiContextAccount	=4,
    apiContextContacts	=8,
};
enum TAttachmentStatus
{
    apiAttachUnknown	=-1,
    apiAttachSuccess	=0,
    apiAttachPendingAuthorization	=1,
    apiAttachRefused	=2,
    apiAttachNotAvailable	=3,
    apiAttachAvailable	=4,
};
enum TBuddyStatus
{
    budUnknown	=-1,
    budNeverBeenFriend	=0,
    budDeletedFriend	=1,
    budPendingAuthorization	=2,
    budFriend	=3,
};
enum TCallChannelType
{
    cctUnknown	=-1,
    cctDatagram	=0,
    cctReliable	=1,
};
enum TCallFailureReason
{
    cfrUnknown	=-1,
    cfrMiscError	=0,
    cfrUserDoesNotExist	=1,
    cfrUserIsOffline	=2,
    cfrNoProxyFound	=3,
    cfrSessionTerminated	=4,
    cfrNoCommonCodec	=5,
    cfrSoundIOError	=6,
    cfrRemoteDeviceError	=7,
    cfrBlockedByRecipient	=8,
    cfrRecipientNotFriend	=9,
    cfrNotAuthorizedByRecipient	=10,
    cfrSoundRecordingError	=11,
};
enum TCallHistory
{
    chsAllCalls	=0,
    chsMissedCalls	=1,
    chsIncomingCalls	=2,
    chsOutgoingCalls	=3,
};
enum TCallIoDeviceType
{
    callIoDeviceTypeUnknown	=-1,
    callIoDeviceTypeSoundcard	=0,
    callIoDeviceTypePort	=1,
    callIoDeviceTypeFile	=2,
};
enum TCallStatus
{
    clsUnknown	=-1,
    clsUnplaced	=0,
    clsRouting	=1,
    clsEarlyMedia	=2,
    clsFailed	=3,
    clsRinging	=4,
    clsInProgress	=5,
    clsOnHold	=6,
    clsFinished	=7,
    clsMissed	=8,
    clsRefused	=9,
    clsBusy	=10,
    clsCancelled	=11,
    clsLocalHold	=12,
    clsRemoteHold	=13,
    clsVoicemailBufferingGreeting	=14,
    clsVoicemailPlayingGreeting	=15,
    clsVoicemailRecording	=16,
    clsVoicemailUploading	=17,
    clsVoicemailSent	=18,
    clsVoicemailCancelled	=19,
    clsVoicemailFailed	=20,
    clsTransferring	=21,
    clsTransferred	=22,
};
enum TCallType
{
    cltUnknown	=-1,
    cltIncomingPSTN	=0,
    cltOutgoingPSTN	=1,
    cltIncomingP2P	=2,
    cltOutgoingP2P	=3,
};
enum TCallVideoSendStatus
{
    vssUnknown	=-1,
    vssNotAvailable	=0,
    vssAvailable	=1,
    vssStarting	=2,
    vssRejected	=3,
    vssRunning	=4,
    vssStopping	=5,
    vssPaused	=6,
};
enum TCallVideoStatus
{
    cvsUnknown	=-1,
    cvsNone	=0,
    cvsSendEnabled	=1,
    cvsReceiveEnabled	=2,
    cvsBothEnabled	=3,
};
enum TChatLeaveReason
{
    leaUnknown	=-1,
    leaUserNotFound	=0,
    leaUserIncapable	=1,
    leaAdderNotFriend	=2,
    leaAddedNotAuthorized	=3,
    leaAddDeclined	=4,
    leaUnsubscribe	=5,
};
enum TChatMemberRole
{
    chatMemberRoleUnknown	=-1,
    chatMemberRoleCreator	=0,
    chatMemberRoleMaster	=1,
    chatMemberRoleHelper	=2,
    chatMemberRoleUser	=3,
    chatMemberRoleListener	=4,
    chatMemberRoleApplicant	=5,
};
enum TChatMessageStatus
{
    cmsUnknown	=-1,
    cmsSending	=0,
    cmsSent	=1,
    cmsReceived	=2,
    cmsRead	=3,
};
enum TChatMessageType
{
    cmeUnknown	=-1,
    cmeCreatedChatWith	=0,
    cmeSawMembers	=1,
    cmeAddedMembers	=2,
    cmeSetTopic	=3,
    cmeSaid	=4,
    cmeLeft	=5,
    cmeEmoted	=6,
    cmePostedContacts	=7,
    cmeGapInChat	=8,
    cmeSetRole	=9,
    cmeKicked	=10,
    cmeSetOptions	=11,
    cmeKickBanned	=12,
    cmeJoinedAsApplicant	=13,
    cmeSetPicture	=14,
    cmeSetGuidelines	=15,
};
enum TChatMyStatus
{
    chatStatusUnknown	=-1,
    chatStatusConnecting	=0,
    chatStatusWaitingRemoteAccept	=1,
    chatStatusAcceptRequired	=2,
    chatStatusPasswordRequired	=3,
    chatStatusSubscribed	=4,
    chatStatusUnsubscribed	=5,
    chatStatusDisbanded	=6,
    chatStatusQueuedBecauseChatIsFull	=7,
    chatStatusApplicationDenied	=8,
    chatStatusKicked	=9,
    chatStatusBanned	=10,
    chatStatusRetryConnecting	=11,
};
enum TChatStatus
{
    chsUnknown	=-1,
    chsLegacyDialog	=0,
    chsDialog	=1,
    chsMultiNeedAccept	=2,
    chsMultiSubscribed	=3,
    chsUnsubscribed	=4,
};
enum TChatType
{
    chatTypeUnknown	=-1,
    chatTypeDialog	=0,
    chatTypeLegacyDialog	=1,
    chatTypeLegacyUnsubscribed	=2,
    chatTypeMultiChat	=3,
    chatTypeSharedGroup	=4,
};
enum TConnectionStatus
{
    conUnknown	=-1,
    conOffline	=0,
    conConnecting	=1,
    conPausing	=2,
    conOnline	=3,
};
enum TFileTransferFailureReason
{
    fileTransferFailureReasonSenderNotAuthorized	=1,
    fileTransferFailureReasonRemotelyCancelled	=2,
    fileTransferFailureReasonFailedRead	=3,
    fileTransferFailureReasonFailedRemoteRead	=4,
    fileTransferFailureReasonFailedWrite	=5,
    fileTransferFailureReasonFailedRemoteWrite	=6,
    fileTransferFailureReasonRemoteDoesNotSupportFT	=7,
    fileTransferFailureReasonRemoteOfflineTooLong	=8,
};
enum TFileTransferStatus
{
    fileTransferStatusNew	=0,
    fileTransferStatusConnecting	=1,
    fileTransferStatusWaitingForAccept	=2,
    fileTransferStatusTransferring	=3,
    fileTransferStatusTransferringOverRelay	=4,
    fileTransferStatusPaused	=5,
    fileTransferStatusRemotelyPaused	=6,
    fileTransferStatusCancelled	=7,
    fileTransferStatusCompleted	=8,
    fileTransferStatusFailed	=9,
};
enum TFileTransferType
{
    fileTransferTypeIncoming	=0,
    fileTransferTypeOutgoing	=1,
};
enum TGroupType
{
    grpUnknown	=-1,
    grpCustomGroup	=0,
    grpAllUsers	=1,
    grpAllFriends	=2,
    grpSkypeFriends	=3,
    grpSkypeOutFriends	=4,
    grpOnlineFriends	=5,
    grpPendingAuthorizationFriends	=6,
    grpRecentlyContactedUsers	=7,
    grpUsersWaitingMyAuthorization	=8,
    grpUsersAuthorizedByMe	=9,
    grpUsersBlockedByMe	=10,
    grpUngroupedFriends	=11,
    grpSharedGroup	=12,
    grpProposedSharedGroup	=13,
};
enum TOnlineStatus
{
    olsUnknown	=-1,
    olsOffline	=0,
    olsOnline	=1,
    olsAway	=2,
    olsNotAvailable	=3,
    olsDoNotDisturb	=4,
    olsSkypeOut	=5,
    olsSkypeMe	=6,
};
enum TPluginContactType
{
    pluginContactTypeUnknown	=-1,
    pluginContactTypeAll	=0,
    pluginContactTypeSkype	=1,
    pluginContactTypeSkypeOut	=2,
};
enum TPluginContext
{
    pluginContextUnknown	=-1,
    pluginContextChat	=0,
    pluginContextCall	=1,
    pluginContextContact	=2,
    pluginContextMyself	=3,
    pluginContextTools	=4,
};
enum TSmsFailureReason
{
    smsFailureReasonUnknown	=-1,
    smsFailureReasonMiscError	=0,
    smsFailureReasonServerConnectFailed	=1,
    smsFailureReasonNoSmsCapability	=2,
    smsFailureReasonInsufficientFunds	=3,
    smsFailureReasonInvalidConfirmationCode	=4,
    smsFailureReasonUserBlocked	=5,
    smsFailureReasonIPBlocked	=6,
    smsFailureReasonNodeBlocked	=7,
};
enum TSmsMessageStatus
{
    smsMessageStatusUnknown	=-1,
    smsMessageStatusReceived	=0,
    smsMessageStatusRead	=1,
    smsMessageStatusComposing	=2,
    smsMessageStatusSendingToServer	=3,
    smsMessageStatusSentToServer	=4,
    smsMessageStatusDelivered	=5,
    smsMessageStatusSomeTargetsFailed	=6,
    smsMessageStatusFailed	=7,
};
enum TSmsMessageType
{
    smsMessageTypeUnknown	=-1,
    smsMessageTypeIncoming	=0,
    smsMessageTypeOutgoing	=1,
    smsMessageTypeCCRequest	=2,
    smsMessageTypeCCSubmit	=3,
};
enum TSmsTargetStatus
{
    smsTargetStatusUnknown	=-1,
    smsTargetStatusUndefined	=0,
    smsTargetStatusAnalyzing	=1,
    smsTargetStatusAcceptable	=2,
    smsTargetStatusNotRoutable	=3,
    smsTargetStatusDeliveryPending	=4,
    smsTargetStatusDeliverySuccessful	=5,
    smsTargetStatusDeliveryFailed	=6,
};
enum TUserSex
{
    usexUnknown	=-1,
    usexMale	=0,
    usexFemale	=1,
};
enum TUserStatus
{
    cusUnknown	=-1,
    cusOffline	=0,
    cusOnline	=1,
    cusAway	=2,
    cusNotAvailable	=3,
    cusDoNotDisturb	=4,
    cusInvisible	=5,
    cusLoggedOut	=6,
    cusSkypeMe	=7,
};
enum TVoicemailFailureReason
{
    vmrUnknown	=-1,
    vmrNoError	=0,
    vmrMiscError	=1,
    vmrConnectError	=2,
    vmrNoPrivilege	=3,
    vmrNoVoicemail	=4,
    vmrFileReadError	=5,
    vmrFileWriteError	=6,
    vmrRecordingError	=7,
    vmrPlaybackError	=8,
};
enum TVoicemailStatus
{
    vmsUnknown	=-1,
    vmsNotDownloaded	=0,
    vmsDownloading	=1,
    vmsUnplayed	=2,
    vmsBuffering	=3,
    vmsPlaying	=4,
    vmsPlayed	=5,
    vmsBlank	=6,
    vmsRecording	=7,
    vmsRecorded	=8,
    vmsUploading	=9,
    vmsUploaded	=10,
    vmsDeleting	=11,
    vmsFailed	=12,
};
enum TVoicemailType
{
    vmtUnknown	=-1,
    vmtIncoming	=0,
    vmtDefaultGreeting	=1,
    vmtCustomGreeting	=2,
    vmtOutgoing	=3,
};




class Skype : public QAxObject
{
    Q_OBJECT
public:
    explicit Skype(QString objectCom, QObject *parent = 0);
    ~Skype();
    bool IsRunning();
    void startSkype();
    void exitSkype();
    QList <QString> getTopicChatsList();
    QString getNameChat(QString topic);
    QString getTopicChat(QString name);
    void sendMessageChat(QString name,QString message);
Q_SIGNALS:
    void ApplicationConnecting(IDispatch* pApp, IDispatch* pUsers);
    void ApplicationDatagram(IDispatch* pApp, IDispatch* pStream, QString Text);
    void ApplicationReceiving(IDispatch* pApp, IDispatch* pStreams);
    void ApplicationSending(IDispatch* pApp, IDispatch* pStreams);
    void ApplicationStreams(IDispatch* pApp, IDispatch* pStreams);
    void AsyncSearchUsersFinished(int Cookie, IDispatch* pUsers);
    void AttachmentStatus(TAttachmentStatus Status);
    void AutoAway(bool Automatic);
    void CallDtmfReceived(IDispatch* pCall, QString code);
    void CallHistory();
    void CallInputStatusChanged(IDispatch* pCall, bool Status);
    void CallSeenStatusChanged(IDispatch* pCall, bool Status);
    void CallStatus(IDispatch* pCall, TCallStatus Status);
    void CallTransferStatusChanged(IDispatch* pCall, TCallStatus Status);
    void CallVideoReceiveStatusChanged(IDispatch* pCall, TCallVideoSendStatus Status);
    void CallVideoSendStatusChanged(IDispatch* pCall, TCallVideoSendStatus Status);
    void CallVideoStatusChanged(IDispatch* pCall, TCallVideoStatus Status);
    void ChatMemberRoleChanged(IDispatch* pMember, TChatMemberRole Role);
    void ChatMembersChanged(IDispatch* pChat, IDispatch* pMembers);
    void Command(IDispatch* pCommand);
    void ConnectionStatus(TConnectionStatus Status);
    void ContactsFocused(QString Username);
    void Error(IDispatch* pCommand, int Number, QString Description);
    void FileTransferStatusChanged(IDispatch* pTransfer, TFileTransferStatus Status);
    void GroupDeleted(int GroupId);
    void GroupExpanded(IDispatch* pGroup, bool Expanded);
    void GroupUsers(IDispatch* pGroup, IDispatch* pUsers);
    void GroupVisible(IDispatch* pGroup, bool Visible);
    void MessageHistory(QString Username);
    void MessageStatus(IDispatch* pMessage, TChatMessageStatus Status);
    void Mute(bool Mute);
    void OnlineStatus(IDispatch* pUser, TOnlineStatus Status);
    void PluginEventClicked(IDispatch* pEvent);
    void PluginMenuItemClicked(IDispatch* pMenuItem, IDispatch* pUsers, TPluginContext PluginContext, QString ContextId);
    void Reply(IDispatch* pCommand);
    void SilentModeStatusChanged(bool Silent);
    void SmsMessageStatusChanged(IDispatch* pMessage, TSmsMessageStatus Status);
    void SmsTargetStatusChanged(IDispatch* pTarget, TSmsTargetStatus Status);
    void UILanguageChanged(QString code);
    void UserAuthorizationRequestReceived(IDispatch* pUser);
    void UserMood(IDispatch* pUser, QString MoodText);
    void UserStatus(TUserStatus Status);
    void VoicemailStatus(IDispatch* pMail, TVoicemailStatus Status);
    void WallpaperChanged(QString Path);


public slots:

private:
    void initChats();

private:
   QAxObject * client;
   QMap <QString, QString> AxChatsName; // Возвращает реальное имя чата по топику
   QAxObject * objectsChats;
   QMap <QString, QAxObject *> AxChatsPointer; // Возвращает указатель на объект чата по реальному имени

};

#endif // SKYPE_H
