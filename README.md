# Theta-Xi-Chore-scheduler

This program generates randomly assigned details based on which house they live in, and their status as a pledge or eboard. The sheets are output in markdown format, these can be openned in a markdown editor of your choice but it is configured to automatically run a bundled markdown editor for viewing and printing.


## configuration:
### Names

- Each person's name/number should go in every file that is applicable to them. An eboard who lives in the new house will go in the eboard file and the new house file. A pledge who lives in the new house will go in the pledges file and the new house file. This is so that you can just look as the room assignments and naively put peoples' names in.
- - **IMPORTANT: Spaces matter in names. Make sure that there are no unwanted spaces in front of or behind the names. If a pledge has an extra space in their name in the pledge folder, he may not be counted as a plege. (Same for eboards)**


### Pledges

- Pledge names will be given a timestamp the first time the program sees their name on the list. After 30 days, the next time the program is run, their name will automatically be removed from the pledge list
- Its never too late to add another pledge. Their 30 day timer start the first time the program is run with them.


### Details

- Details should be formatted as such: `<label>:<days>:<number of people required>` 
- Ex: Breezeway & Yard & Dumps:MWF:2
- M = Monday, T = Tuesday, W = Wednesday, H = Thursday, F = Friday, S = Saturday, U = Sunday
- The number of people is a maximum of 9
- Its a good practice to make sure there are no eronious spaces
- If there are too few people in a category, there will be details which are missing people. There will also be a warning at the bottom of the output file file.



