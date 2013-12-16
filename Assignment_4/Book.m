//
//  Book.m
//  Assignment_4_Book_Class
//
//  Created by David on 12/15/13.
//  Copyright (c) 2013 David Bulnes. All rights reserved.
//

#import "Book.h"

/*
 NOTE: For this assignment I am presuming use of XCode 4.4+. Therefore, instance variables of
 properties are auto-synthesized.

 Automatic Reference Counting is used.
 
 It is my judgment that the compiler-generated accessors for the Book's properties are adequate in this case.
 Perhaps if we had data persistence with Core Data, or elsewhere in memory, we could check for
 duplicate titles, authors, and publication years to prevent duplicate books and for better grouping of books.
 Also, if custom property accessors were implemented, it would necessitate the @synthesize directive
 for each properties' instance variable.
*/

@implementation Book

- (id)initWithTitle:(NSString *)title
                 author:(NSString *)author
        publicationYear:(int)publicationYear
{
    //Initialize NSObject superclass and assign properties.
    if (self = [super init]) {
        self.title = title;
        self.author = author;
        self.publicationYear = publicationYear;
        return self;
    }
    //[self release]; //Would be here if not using Automatic Reference Counting.
    NSLog(@"Error initializing Book superclass.");
    return nil;
}

- (void)printBookInformationOnConsole
{
    NSString *title = self.title.length ? self.title : @"No title set.";
    NSString *author = self.author.length ? self.author : @"No author set.";
    NSString *publicationYear = self.publicationYear ? [[NSString alloc] initWithFormat:@"%d", self.publicationYear] : @"No";
    NSLog(@"This Book's Information:\nTitle: %@\nAuthor: %@\n Publication: %@\n", title, author, publicationYear);
}

@end
