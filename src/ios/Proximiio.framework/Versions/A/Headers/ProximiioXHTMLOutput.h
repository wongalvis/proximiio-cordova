//
//  ProximiioXHTMLOutput.h
//  Proximiio
//
//  Created by Marian Frische on 23.04.15.
//  Copyright (c) 2015 NavtureApps. All rights reserved.
//

#import "ProximiioOutput.h"
#import <UIKit/UIKit.h>


/*!
 @interface ProximiioXHTMLOutput
 @brief ProximiioXHTMLOutput interface.
 */
@interface ProximiioXHTMLOutput : ProximiioOutput

/*!
 @brief Title string of the XHTML page.
 */
@property (nonatomic, readonly) NSString *title;
/*!
 @brief XHTML content string.
 */
@property (nonatomic, readonly) NSString *content;


/*!
 @brief Inits a @c ProximiioXHTMLOutput instance.
 
 @param ID
 Unique Input ID.
 @param title
 Title string of the XHTML page.
 @param content
 XHTML content string.
 
 @return An initialized @c ProximiioXHTMLOutput instance.
 */
- (ProximiioXHTMLOutput*)initWithID:(NSString*)ID title:(NSString*)title andContent:(NSString*)content;

/*!
 @brief Loads the content into a given @c UIWebView.
 
 @param webView
 The webview into which the XHTML will be loaded.
 */
- (void)showInWebView:(UIWebView*)webView;

@end
