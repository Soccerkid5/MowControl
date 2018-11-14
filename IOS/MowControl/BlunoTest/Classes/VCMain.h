//
//  VCMain.h
//  BlunoTest
//
//  Created by Seifer on 13-12-1.
//  Copyright (c) 2013年 DFRobot. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DFBlunoManager.h"

@interface VCMain : UIViewController<DFBlunoDelegate>
@property(strong, nonatomic) DFBlunoManager* blunoManager;
@property(strong, nonatomic) DFBlunoDevice* blunoDev;
@property(strong, nonatomic) NSMutableArray* aryDevices;

@property (weak, nonatomic) IBOutlet UILabel *lbReceivedMsg;
@property (weak, nonatomic) IBOutlet UITextField *txtSendMsg;
@property (weak, nonatomic) IBOutlet UILabel *lbReady;

@property (strong, nonatomic) IBOutlet UIView *viewDevices;
@property (strong, nonatomic) IBOutlet UIView *navigation;
@property (weak, nonatomic) IBOutlet UITableView *tbDevices;

@property (weak, nonatomic) IBOutlet UIActivityIndicatorView *SearchIndicator;
@property (strong, nonatomic) IBOutlet UITableViewCell *cellDevices;
@property (strong, nonatomic) IBOutlet UILabel *blades;

@property (strong, nonatomic) IBOutlet UISwitch *bladeswitch;
@property (strong, nonatomic) IBOutlet UISwitch *manualswitch;
@property (strong, nonatomic) IBOutlet UISwitch *autonomousslider;
@property (strong, nonatomic) IBOutlet UIButton *UpArrow;
@property (strong, nonatomic) IBOutlet UIButton *RightArrow;
@property (strong, nonatomic) IBOutlet UIButton *DownArrow;
@property (strong, nonatomic) IBOutlet UIButton *LeftArrow;
@property (strong, nonatomic) IBOutlet UIButton *returnswitch;
@property (strong, nonatomic) IBOutlet UILabel *manual;
@property (strong, nonatomic) IBOutlet UILabel *autonomous;


- (IBAction)actionSearch:(id)sender;
- (IBAction)actionReturn:(id)sender;
- (IBAction)actionSend:(id)sender;
- (IBAction)actionDidEnd:(id)sender;
- (IBAction)bladeswitch:(id)sender;
- (IBAction)uparrow:(id)sender;
- (IBAction)rightarrow:(id)sender;
- (IBAction)downarrow:(id)sender;
- (IBAction)leftarrow:(id)sender;
- (IBAction)returnswitch:(id)sender;
- (IBAction)mswitch:(id)sender;
- (IBAction)autonomousslider:(id)sender;



@end
