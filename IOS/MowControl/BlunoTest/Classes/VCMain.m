//
//  VCMain.m
//  BlunoTest
//
//  Created by Seifer on 13-12-1.
//  Copyright (c) 2013年 DFRobot. All rights reserved.
//

#import "VCMain.h"

@interface VCMain ()

@end

@implementation VCMain

#pragma mark- LifeCycle

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.blunoManager = [DFBlunoManager sharedInstance];
    self.blunoManager.delegate = self;
    self.aryDevices = [[NSMutableArray alloc] init];
    self.lbReady.text = @"Not Ready!";
    [self.manualswitch setOn:NO animated:YES];
    [self.autonomousslider setOn:NO animated:YES];
    [self.bladeswitch setOn:NO animated:YES];
    
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark- Actions

- (IBAction)actionSearch:(id)sender
{
    [self.aryDevices removeAllObjects];
    [self.tbDevices reloadData];
    [self.SearchIndicator startAnimating];
    self.viewDevices.hidden = NO;
    
    [self.blunoManager scan];
}

- (IBAction)actionReturn:(id)sender
{
    [self.SearchIndicator stopAnimating];
    [self.blunoManager stop];
    self.viewDevices.hidden = YES;
}

- (IBAction)actionSend:(id)sender
{
    [self.txtSendMsg resignFirstResponder];
    if (self.blunoDev.bReadyToWrite)
    {
        NSString* strTemp = self.txtSendMsg.text;
        NSData* data = [strTemp dataUsingEncoding:NSUTF8StringEncoding];
        [self.blunoManager writeDataToDevice:data Device:self.blunoDev];
    }
}

- (IBAction)actionDidEnd:(id)sender
{
    [self.txtSendMsg resignFirstResponder];
}


- (IBAction)bladeswitch:(id)sender {
    
    if([_bladeswitch isOn])
    {
        if (self.blunoDev.bReadyToWrite)
        {
            
            NSString* strTemp = @"o";
            NSData* data = [strTemp dataUsingEncoding:NSUTF8StringEncoding];
            [self.blunoManager writeDataToDevice:data Device:self.blunoDev];
        }
    }
    else
    {
        if (self.blunoDev.bReadyToWrite)
        {
            
            NSString* strTemp = @"n";
            NSData* data = [strTemp dataUsingEncoding:NSUTF8StringEncoding];
            [self.blunoManager writeDataToDevice:data Device:self.blunoDev];
        }
    }
}

- (IBAction)uparrow:(id)sender {
    if (self.blunoDev.bReadyToWrite)
    {
        NSString* strTemp = @"f";
        NSData* data = [strTemp dataUsingEncoding:NSUTF8StringEncoding];
        [self.blunoManager writeDataToDevice:data Device:self.blunoDev];
    }
}

- (IBAction)rightarrow:(id)sender {
    if (self.blunoDev.bReadyToWrite)
    {
        NSString* strTemp = @"r";
        NSData* data = [strTemp dataUsingEncoding:NSUTF8StringEncoding];
        [self.blunoManager writeDataToDevice:data Device:self.blunoDev];
    }
}

- (IBAction)downarrow:(id)sender {
    if (self.blunoDev.bReadyToWrite)
    {
        NSString* strTemp = @"s";
        NSData* data = [strTemp dataUsingEncoding:NSUTF8StringEncoding];
        [self.blunoManager writeDataToDevice:data Device:self.blunoDev];
    }
}

- (IBAction)leftarrow:(id)sender {
    
    if (self.blunoDev.bReadyToWrite)
    {
        NSString* strTemp = @"l";
        NSData* data = [strTemp dataUsingEncoding:NSUTF8StringEncoding];
        [self.blunoManager writeDataToDevice:data Device:self.blunoDev];
    }
}

- (IBAction)returnswitch:(id)sender {
    
    self.navigation.hidden = YES;
    [self.manualswitch setOn:NO animated:YES];
    if (self.blunoDev.bReadyToWrite)
    {
        NSString* strTemp = @"x";
        NSData* data = [strTemp dataUsingEncoding:NSUTF8StringEncoding];
        [self.blunoManager writeDataToDevice:data Device:self.blunoDev];
    }
    
}

- (IBAction)mswitch:(id)sender {
    
    if ([_manualswitch isOn])
    {
        self.navigation.hidden = NO;
        if (self.blunoDev.bReadyToWrite)
        {
            NSString* strTemp = @"u";
            NSData* data = [strTemp dataUsingEncoding:NSUTF8StringEncoding];
            [self.blunoManager writeDataToDevice:data Device:self.blunoDev];
        }
        
    }
    else
    {
        self.navigation.hidden = YES;

    }
}

- (IBAction)autonomousslider:(id)sender {
    
    if([_autonomousslider isOn])
    {
        if (self.blunoDev.bReadyToWrite)
        {
            
            NSString* strTemp = @"y";
            NSData* data = [strTemp dataUsingEncoding:NSUTF8StringEncoding];
            [self.blunoManager writeDataToDevice:data Device:self.blunoDev];
        }
    }
    else
    {
        if (self.blunoDev.bReadyToWrite)
        {
            
            NSString* strTemp = @"x";
            NSData* data = [strTemp dataUsingEncoding:NSUTF8StringEncoding];
            [self.blunoManager writeDataToDevice:data Device:self.blunoDev];
        }
    }
    
}

#pragma mark- DFBlunoDelegate

-(void)bleDidUpdateState:(BOOL)bleSupported
{
    if(bleSupported)
    {
        [self.blunoManager scan];
    }
}
-(void)didDiscoverDevice:(DFBlunoDevice*)dev
{
    BOOL bRepeat = NO;
    for (DFBlunoDevice* bleDevice in self.aryDevices)
    {
        if ([bleDevice isEqual:dev])
        {
            bRepeat = YES;
            break;
        }
    }
    if (!bRepeat)
    {
        [self.aryDevices addObject:dev];
    }
    [self.tbDevices reloadData];
}
-(void)readyToCommunicate:(DFBlunoDevice*)dev
{
    self.blunoDev = dev;
    self.lbReady.text = @"Ready!";
}
-(void)didDisconnectDevice:(DFBlunoDevice*)dev
{
    self.lbReady.text = @"Not Ready!";
}
-(void)didWriteData:(DFBlunoDevice*)dev
{
    
}
-(void)didReceiveData:(NSData*)data Device:(DFBlunoDevice*)dev
{
    self.lbReceivedMsg.text = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
}

#pragma mark- TableViewDataSource

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    NSInteger nCount = [self.aryDevices count];
    return nCount;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *MyIdentifier = @"ScanDeviceCell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:MyIdentifier];
    
    if (cell == nil)
    {
        if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone)
        {
            [[NSBundle mainBundle] loadNibNamed:@"CellDeviceList" owner:self options:nil];
        }
        else
        {
            
        }
        
        cell = self.cellDevices;
	}
    
    UILabel* lbName             = (UILabel*)[cell viewWithTag:1];
    UILabel* lbUUID             = (UILabel*)[cell viewWithTag:2];
    DFBlunoDevice* peripheral   = [self.aryDevices objectAtIndex:indexPath.row];
    
    lbName.text = peripheral.name;
    lbUUID.text = peripheral.identifier;
    
    return cell;
    
}


#pragma mark- TableView Delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    DFBlunoDevice* device = [self.aryDevices objectAtIndex:indexPath.row];
    if (self.blunoDev == nil)
    {
        self.blunoDev = device;
        [self.blunoManager connectToDevice:self.blunoDev];
    }
    else if ([device isEqual:self.blunoDev])
    {
        if (!self.blunoDev.bReadyToWrite)
        {
            [self.blunoManager connectToDevice:self.blunoDev];
        }
    }
    else
    {
        if (self.blunoDev.bReadyToWrite)
        {
            [self.blunoManager disconnectToDevice:self.blunoDev];
            self.blunoDev = nil;
        }
        
        [self.blunoManager connectToDevice:device];
    }
    self.viewDevices.hidden = YES;
    [self.SearchIndicator stopAnimating];
}

@end
