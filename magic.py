import random

def shuffle( deck ):
    random.seed( None )
    for i in range( len( deck ) ):
        switch = random.randint( 0, 26 )

        # swap card at position i 
        temp = deck[switch]
        deck[switch] = deck[i]
        deck[i] = temp

def which_group( deck ):
    print( "Now tell me: which group is the card in?" )
    print( "First?" )
    print( [ deck[i] for i in range( 0, 9 ) ] )
    print( "Second?" )
    print( [ deck[i] for i in range( 9, 18 ) ] )
    print( "Third?" )
    print( [ deck[i] for i in range( 18, 27 ) ] )

# Gets the group the user chose
def get_group( deck, choice ):
    if ( choice == 1 ):
        return [ deck[i] for i in range( 0, 9 ) ]
    elif ( choice == 2 ):
        return [ deck[i] for i in range( 9, 18 ) ] 
    elif ( choice == 3 ):
        return [ deck[i] for i in range( 18, 27 ) ]

# Gets user's choice from 1 to 3
def get_choice():
    while( True ):
        user_input = input()
        try:
            user_input = int( user_input )
        except( ValueError ):
            print( "Enter a number from 1 to 3" )
            continue

        if ( user_input >= 1 and user_input <= 3 ):
            break
        else:
            print( "Enter a number from 1 to 3" )

    return user_input

def shift_values( deck ):
    new_deck = []
    for i in range( 9 ):
        new_deck.append( deck[i] )
        new_deck.append( deck[i + 9] )
        new_deck.append( deck[i + 18] )
    return new_deck

def main():
    print( "##################" )
    print( "#                #" )
    print( "#   MAGIC SHOW   #" )
    print( "#                #" )
    print( "##################\n" )

    print( "Welcome to the magic show. Get ready to pick a number any number! \n(Must be an integer between 1 and 27 inclusively) \n" )

    deck = [ i+1 for i in range(27) ]
    shuffle( deck )

    which_group( deck )
    set1 = get_group( deck, get_choice() )

    deck = shift_values( deck )
    which_group( deck )
    set2 = get_group( deck, get_choice() )

    deck = shift_values( deck )
    which_group( deck )
    set3 = get_group( deck, get_choice() )

    print( "\nYour number was " + \
               str( list( set(set1).intersection( set(set2), set(set3) ) )[0] )\
               + ". Wasn't it?" )

    print( "Disclaimer: Any error in the result is due to human error i.e. you" )

if __name__ == '__main__':
    main()
