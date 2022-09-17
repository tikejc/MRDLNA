//
//  MRDLNA.h
//  MRDLNA
//
//  Created by MccRee on 2018/5/4.
//

#import <Foundation/Foundation.h>
#import "CLUPnP.h"
#import "CLUPnPDevice.h"
typedef enum : NSUInteger {
    DLNAStatePlay,
    DLNAStatePause,
    DLNAStateStop,
} DLNAState;

typedef enum : NSUInteger {
    DLNAEventSeek,
    DLNAEventPrevious,
    DLNAEventNext,
    DLNAEventNextURI,
    DLNAEventVolume,
} DLNAEvent;
@class MRDLNA;
@protocol DLNADelegate <NSObject>

@optional
/**
 DLNA局域网搜索设备结果
 @param devicesArray <CLUPnPDevice *> 搜索到的设备
 */
- (void)searchDLNAResult:(NSArray *)devicesArray;
- (void)mrDidStartSearch:(MRDLNA *)mrdlna;
- (void)mrDidStopSearch:(MRDLNA *)mrdlna;
- (void)mrDLNA:(MRDLNA*)mdrlna event:(DLNAEvent)event;
- (void)mrDLNA:(MRDLNA*)mdrlna state:(DLNAState)state;
/**
 投屏成功开始播放
 */
- (void)dlnaStartPlay;

@end



@interface MRDLNA : NSObject

@property(nonatomic,weak)id<DLNADelegate> delegate;

@property(nonatomic, strong) CLUPnPDevice *device;

@property(nonatomic,copy) NSString *playUrl;

@property(nonatomic,assign) NSInteger searchTime;

@property (nonatomic, assign) DLNAState state;
/**
 单例
 */
+(instancetype)sharedMRDLNAManager;

/**
 搜设备
 */
- (void)startSearch;

/**
 DLNA投屏
 */
- (void)startDLNA;
/**
 DLNA投屏(首先停止)---投屏不了可以使用这个方法
 ** 【流程: 停止 ->设置代理 ->设置Url -> 播放】
 */
- (void)startDLNAAfterStop;

/**
 退出DLNA
 */
- (void)endDLNA;

/**
 播放
 */
- (void)dlnaPlay;

/**
 暂停
 */
- (void)dlnaPause;

- (void)volumeChanged:(NSString *)volume DEPRECATED_MSG_ATTRIBUTE("直接使用volume");

/**
 设置播放进度 seek单位是秒
 */
- (void)seekChanged:(NSInteger)seek;

/**
 播放切集
 */
- (void)playTheURL:(NSString *)url;
/**
 获取播放进度 切记在回调执行后再执行下一次获取进度的操作
 */
- (void)getSeekTime:(void (^)(CLUPnPAVPositionInfo *)) block;

///  音量  设置音量 volume建议传0-100
@property (nonatomic, assign) NSInteger volume;
@end
