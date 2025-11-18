# Theta-Xi-chore-scheduler

This program generates randomly assigned details based on which house people live in, and their status as a pledge or eboard. The sheets are output in markdown format, these can be openned in a markdown editor of your choice but it's currently configured to automatically run a bundled markdown editor for viewing, editing, and printing.

## requirements:

- [x] Details are on set days with a set number of people on a detail.
- [x] It should be easy to create and modify details.
- [x] Eboards should only have 1 detail, which should be a house detail by default.
- [x] Eboards should not get details on monday.
- [x] Everyone else gets a house detail and a community detail by default.
- [x] Pledges only get detail with 2 people for their first month.
- [x] Graduating seniors dont get any details.
- [x] In the case that there are not enough people in the new house to fill the sheet, community detail slots of new-housers can be redirected to fill the remainder of the sheet.
- [x] Detail sheets will be output in a ready-to-print format.

## Basic Usage
When run, the program will prompt the user for a date to be put on the sheet. Then the sheet will be generated. The program can be bundled with a markdown editor called MarkText. If MarkText is present it will be launched, and the sheets can be printed, or exported as a pdf.

## Common Issues
- **IMPORTANT: Please do not ignore the "Too few people for sheet" warning. This is a sign that the output sheet is incomplete.** The number of people specified is not enough to fill the number of detail slots specified. In order to remedy this, you must do one or more of the following: Remove a detail, reduce the number of days that a detail is done on, or reduce the number of people required for a detail.

## Configuration
### Names

- Each person's name/number should go in every file that is applicable to them. An eboard who lives in the new house will go in the eboard file and the new house file. A pledge who lives in the new house will go in the pledges file and the new house file. This is so that you can just look as the room assignments and naively put peoples' names in.
- **IMPORTANT: Spaces matter in names. Make sure that there are no unwanted spaces in front of or behind the names. If a pledge has an extra space in their name in the pledge folder, he may not be counted as a pledge. (Same for eboards)**

### Pledges

- Pledge names will be given a timestamp the first time the program sees their name on the list. After 30 days, the next time the program is run, their name will automatically be removed from the pledge list
- Its never too late to add another pledge. Their 30 day timer start the first time the program is run with them.

### Details

- Details should be formatted as such: `<label>:<days>:<number of people required>` 
- Ex: Breezeway & Yard & Dumps:MWF:2
- M = Monday, T = Tuesday, W = Wednesday, H = Thursday, F = Friday, S = Saturday, U = Sunday
- The number of people is a maximum of 9
- Its a good practice to make sure there are no eronious spaces

### Commenting

- At any point you put an "#", all text after it on that line will be invisible in the eyes of the program.
- This can be used to temporarily remove a detai or a person from the pool, it works in every config file.
- If there are too few people in a category, there will be details which are missing people. There will also be a warning at the bottom of the output file file. 
