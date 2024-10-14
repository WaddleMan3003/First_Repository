#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

//Checks if base is a valid character.
bool isValidBase(char base)
{
    if(base == 'A' || base == 'C' || base == 'G' || base == 'T')
    {
        return true;
    }
    else
    {
        return false;
    }
}

//Checks if strand is made up of valid bases.
bool isValidStrand(string strand)
{
    bool val = false;

    //For every base in the strand.
    for(unsigned int i=0; i < strand.length(); i++)
    {
        //If every base is valid.
        if(isValidBase(strand[i]) == true)
        {
            val = true;
        }
        //If any base is not valid.
        else
        {
            val = false;
            break;
        }
    }
    return val;
}

//Compares how similar two strands of same length are.
double strandSimilarity(string strand1, string strand2)
{
    double position = 0;
    double match = 0;

    //If two strands are not of equal length.
    if(strand1.length() != strand2.length())
    {
        return false;
    }

    //For every base in both strands.
    for(unsigned int i=0; i < strand1.length(); i++)
    {
        //If bases at same position are equal.
        if(strand1[i] == strand2[i])
        {
            position ++;
            match ++;
        }
        //If bases at same position are not equal.
        else
        {
            position ++;
        }
    }
    return match / position;
}

//Finds the best similarity between two strands.
int bestStrandMatch(string input_strand, string target_strand)
{
    int val = 0;
    double test = 0;
    string new_strand;

    //If target strand is of greater length than input strand.
    if(input_strand.length() < target_strand.length())
    {
        val = -1;
        cout << "Best similarity score: 0.0" << endl;
        return val;
    }
    //If input strand and target strand are of equal length.
    else if(input_strand.length() == target_strand.length())
    {
        val = 0;
        cout << "Best similarity score: " << strandSimilarity(input_strand, target_strand) << endl;
        return val;
    }
  
    //For every base in the input strand.
    for(unsigned int i=0; i < input_strand.length(); i++)
    {
        //Substring of input strand is converted to equal length of target strand.
        new_strand = input_strand.substr(i, target_strand.length());
        //If the two strands are equal to each other.
        if(new_strand == target_strand)
        {
            val = i;
            cout << "Best similarity score: " << strandSimilarity(new_strand, target_strand) << endl;
            return val;
        }
        //If the strand similarity between the two strands at a specific position is greater than it was at a previous position.
        else if(strandSimilarity(new_strand, target_strand) > test)
        {
            val = i;
            test = strandSimilarity(new_strand, target_strand);
        }
    }
    cout << "Best similarity score: " << test << endl;
    return val;
}

//Identifies when bases in two strands that have been best aligned do not match, including if they are different, if there is an insertion into the target strand, or if there is a deletion in the target strand.
void identifyMutations(string input_strand, string target_strand)
{
    string new_strand;

    //If target strand is of greater length than input strand, swaps their positions.
    if(input_strand.length() < target_strand.length())
    {
        unsigned int align = bestStrandMatch(target_strand, input_strand);
        cout << "Best alignment index: " << align << endl;
        //Substring of target strand is converted to equal length of input strand.
        new_strand = target_strand.substr(align, input_strand.length());
        //For every base in the target strand.
        for(unsigned int i=0; i < target_strand.length(); i++)
        {
            //If target strand position is before strand alignment.
            if(i < align)
            {
                cout << "Insertion at position " << i+1 << ": " << target_strand[i] << " is inserted in target strand" << endl;
            }
        }
        //For every base in the aligned strands.
        for(unsigned int i=0; i < new_strand.length(); i++)
        {
            //If the bases of the strands do not match when aligned.
            if(new_strand[i] != input_strand[i])
            {
                cout << "Substitution at position " << i+1+align << ": " << input_strand[i] << " -> " << new_strand[i] << endl;
            }
        }
        //For every base in the target strand.
        for(unsigned int i=0; i < target_strand.length(); i++)
        {
            //If target strand position is after strand alignment.
            if(i >= input_strand.length() + align)
            {
                cout << "Insertion at position " << i+1 << ": " << target_strand[i] << " is inserted in target strand" << endl;
            }
        }
    }
    else
    {
        unsigned int align = bestStrandMatch(input_strand, target_strand);
        cout << "Best alignment index: " << align << endl;
        //If the two strands equal each other.
        if(input_strand == target_strand)
        {
            cout << "No mutations found." << endl;
        }
        //Substring of input strand is converted to equal length of target strand.
        new_strand = input_strand.substr(align, target_strand.length());
        //For every base in the input strand.
        for(unsigned int i=0; i < input_strand.length(); i++)
        {
            //If input strand position is before strand alignment.
            if(i < align)
            {
                cout << "Deletion at position " << i+1 << ": " << input_strand[i] << " is deleted in target strand" << endl;
            }
        }
        //For every base in the aligned strands.
        for(unsigned int i=0; i < new_strand.length(); i++)
        {
            //If the bases of the strands do not match when aligned.
            if(new_strand[i] != target_strand[i])
            {
                cout << "Substitution at position " << i+1+align << ": " << new_strand[i] << " -> " << target_strand[i] << endl;
            }
        }
        //For every base in the input strand.
        for(unsigned int i=0; i < input_strand.length(); i++)
        {
            //If input strand position is past the strand alignment.
            if(i >= target_strand.length() + align)
            {
                cout << "Deletion at position " << i+1 << ": " << input_strand[i] << " is deleted in target strand" << endl;
            }
        }
    }
    
}

//Transcibes any base of T to U.
void transcribeDNAtoRNA(string strand)
{
    //For every base in the strand.
    for(unsigned int i=0; i < strand.length(); i++)
    {
        if(strand[i] == 'T')
        {
            strand[i] = 'U';
        }
    }
    cout << strand << endl;
}

//Reverses strand and transcribes all of its bases to their complements.
void reverseComplement(string strand)
{
    //Reverses the strand.
    reverse(strand.begin(), strand.end());
    
    //For every base in the reversed strand.
    for(unsigned int i=0; i < strand.length(); i++)
    {
        if(strand[i] == 'A')
        {
            strand[i] = 'T';
        }
        else if(strand[i] == 'T')
        {
            strand[i] = 'A';
        }
        else if(strand[i] == 'C')
        {
            strand[i] = 'G';
        }
        else if(strand[i] == 'G')
        {
            strand[i] = 'C';
        }
    }
    cout << strand << endl;
}

//Splits bases in a strand into reading frames.
void getCodingFrames(string strand)
{
    string codon = "";
    int val1 = 0;
    int val2 = 0;
    int check = 0;
    //For every base in the strand.
    for(unsigned int i=0; i < strand.length(); i++)
    {
        //If start codon is found.
        if(strand[i] == 'A' && strand[i+1] == 'T' && strand[i+2] == 'G')
        {
            val1 = i;
            val2 = val1;
            //For every base past the start codon.
            for(unsigned int j=val2; j < strand.length(); j++)
            {
                //If end codon is found.
                if((strand[j] == 'T' && strand[j+1] == 'A' && strand[j+2] == 'A') || (strand[j] == 'T' && strand[j+1] == 'A' && strand[j+2] == 'G') || (strand[j] == 'T' && strand[j+1] == 'G' && strand[j+2] == 'A'))
                {
                    val2=j+3;
                    codon = strand.substr(val1, val2-val1);
                    //If length of reading frame is divisible by 3.
                    if(codon.length() % 3 == 0)
                    {
                        cout << codon << endl;
                        check ++;
                        i = j;
                        break;
                    }
                    else
                    {
                        val2 = j;
                    }
                }
            }
        }
    }
    //If no reading frames are found.
    if(check == 0)
    {
        cout << "No reading frames found." << endl;
    }
}

int main()
{
    int choice = 0;

    string strand;

    string strand1;
    string strand2;

    string input_strand;
    string target_strand;

    //While user input has not choosen to quit, display main menu.
    while(choice != 7)
    {
        //If user has not choosen valid option yet.
        if(choice == 0)
        {
            cout << "--- DNA Analysis Menu ---" << endl;
            cout << "1. Calculate the similarity between two sequences of the same length" << endl;
            cout << "2. Calculate the best similarity between two sequences of either equal or unequal length" << endl;
            cout << "3. Identify mutations" << endl;
            cout << "4. Transcribe DNA to RNA" << endl;
            cout << "5. Find the reverse complement of a DNA sequence" << endl;
            cout << "6. Extract coding frames" << endl;
            cout << "7. Exit" << endl;
            cout << "Please enter your choice (1 - 7):" << endl;
            cin >> choice;
        }
        //If user chooses option 1.
        else if(choice == 1)
        {
            cout << "Enter the first DNA sequence:" << endl;
            cin >> strand1;
            //Repeatively ask user for input if entered strand is invalid.
            while(isValidStrand(strand1) == false)
            {
                cout << "Invalid input. Please enter a valid sequence." << endl;
                cout << "Enter the first DNA sequence:" << endl;
                cin >> strand1;
            }
            cout << "Enter the second DNA sequence:" << endl;
            cin >> strand2;
            //Repeatively ask user for input if entered strand is invalid.
            while(isValidStrand(strand2) == false)
            {
                cout << "Invalid input. Please enter a valid sequence." << endl;
                cout << "Enter the second DNA sequence:" << endl;
                cin >> strand2;
            }
            //Display error if strands are not of equal length.
            if(strandSimilarity(strand1, strand2) == false)
            {
                cout << "Error: Input strands must be of the same length." << endl;
                choice = 0;
            }
            else
            {
                cout << "Similarity score: " << strandSimilarity(strand1, strand2) << endl;
                choice = 0;
            }
        }
        //If user chooses option 2.
        else if(choice == 2)
        {
            cout << "Enter the first DNA sequence:" << endl;
            cin >> input_strand;
            //Repeatively ask user for input if entered strand is invalid.
            while(isValidStrand(input_strand) == false)
            {
                cout << "Invalid input. Please enter a valid sequence." << endl;
                cout << "Enter the first DNA sequence:" << endl;
                cin >> input_strand;
            }
            cout << "Enter the second DNA sequence:" << endl;
            cin >> target_strand;
            //Repeatively ask user for input if entered strand is invalid.
            while(isValidStrand(target_strand) == false)
            {
                cout << "Invalid input. Please enter a valid sequence." << endl;
                cout << "Enter the second DNA sequence:" << endl;
                cin >> target_strand;
            }
            bestStrandMatch(input_strand, target_strand);
            choice = 0;
        }
        //If user chooses option 3.
        else if(choice == 3)
        {
            cout << "Enter the first DNA sequence:" << endl;
            cin >> input_strand;
            //Repeatively ask user for input if entered strand is invalid.
            while(isValidStrand(input_strand) == false)
            {
                cout << "Invalid input. Please enter a valid sequence." << endl;
                cout << "Enter the first DNA sequence:" << endl;
                cin >> input_strand;
            }
            //Repeatively ask user for input if entered strand is invalid.
            cout << "Enter the second DNA sequence:" << endl;
            cin >> target_strand;
            while(isValidStrand(target_strand) == false)
            {
                cout << "Invalid input. Please enter a valid sequence." << endl;
                cout << "Enter the second DNA sequence:" << endl;
                cin >> target_strand;
            }
            identifyMutations(input_strand, target_strand);
            choice = 0;
        }
        //If user chooses option 4.
        else if(choice == 4)
        {
            cout << "Enter the DNA sequence to be transcribed:" << endl;
            cin >> strand;
            //Repeatively ask user for input if entered strand is invalid.
            while(isValidStrand(strand) == false)
            {
                cout << "Invalid input. Please enter a valid sequence." << endl;
                cout << "Enter the DNA sequence to be transcribed:" << endl;
                cin >> strand;
            }
            cout << "The transcribed DNA is: ";
            transcribeDNAtoRNA(strand);
            choice = 0;
        }
        //If user chooses option 5.
        else if(choice == 5)
        {
            cout << "Enter the DNA sequence:" << endl;
            cin >> strand;
            //Repeatively ask user for input if entered strand is invalid.
            while(isValidStrand(strand) == false)
            {
                cout << "Invalid input. Please enter a valid sequence." << endl;
                cout << "Enter the DNA sequence:" << endl;
                cin >> strand;
            }
            cout << "The reverse complement is: ";
            reverseComplement(strand);
            choice = 0;
        }
        //If user chooses option 6.
        else if(choice == 6)
        {
            cout << "Enter the DNA sequence:" << endl;
            cin >> strand;
            //Repeatively ask user for input if entered strand is invalid.
            while(isValidStrand(strand) == false)
            {
                cout << "Invalid input. Please enter a valid sequence." << endl;
                cout << "Enter the DNA sequence:" << endl;
                cin >> strand;
            }
            cout << "The extracted reading frames are: " << endl;
            getCodingFrames(strand);
            choice = 0;
        }
        //If user chooses invalid option.
        else
        {
            cout << "Invalid input. Please select a valid option." << endl;
            choice = 0;
        }
    }
    cout << "Exiting program." << endl;

    return 0;
}