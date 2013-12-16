//
//  Book.h
//  Assignment_4_Book_Class
//
//  Created by David on 12/15/13.
//  Copyright (c) 2013 David Bulnes. All rights reserved.
//

/* Assignment 4:
     Apple provides guides to the Objective-C language at:
     https://developer.apple.com/library/mac/documentation/Cocoa/Conceptual/ProgrammingWithObjectiveC/Introduction/Introduction.html
     
     Using the information in these documents, create an Objective-C class, with accompanying header file. 
     The class will represent a book, and should have a title, author, and a year of publication. 
     Be sure to provide a designated initializer and accessors for these properties.
     
     You may optionally provide a small main() function that demonstrates its use.
 */

#import <Foundation/Foundation.h>

@interface Book : NSObject

@property NSString *title;
@property NSString *author;
//No need to use a NSNumber for simple integer value.
//Negative values are allowed for publicationYear as representing B.C. years. 
@property int publicationYear;

- (Book *)initWithTitle:(NSString *)title
                 author:(NSString *)author
        publicationYear:(int)publicationYear;

- (void)printBookInformationOnConsole;

@end
