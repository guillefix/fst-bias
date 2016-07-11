import numpy as np
def KC_LZ(string):
    n=len(string)
    s = '0'+string
    c=1
    l=1
    i=0
    k=1
    k_max=1
    stop=0

    while stop==0:
        if s[i+k] != s[l+k]:
            if k>k_max:
                k_max=k # k_max stores the length of the longest pattern in the LA that has been matched somewhere in the SB

            i=i+1 # we increase i while the bit doesn't match, looking for a previous occurence of a pattern. s[i+k] is scanning the "search buffer" (SB)

            if i==l: # we stop looking when i catches up with the first bit of the "look-ahead" (LA) part.
                c=c+1 # If we were actually compressing, we would add the new token here. here we just count recounstruction STEPs
                l=l+k_max # we move the beginning of the LA to the end of the newly matched pattern.

                if l+1>n: # if the LA surpasses length of string, then we stop.
                    stop=1

                else: #after STEP,
                    i=0 # we reset the searching index to beginning of SB (beginning of string)
                    k=1 # we reset pattern matching index. Note that we are actually matching against the first bit of the string, because we added an extra 0 above, so i+k is the first bit of the string.
                    k_max=1 # and we reset max lenght of matched pattern to k.
            else:
                k=1 #we've finished matching a pattern in the SB, and we reset the matched pattern length counter.

        else: # I increase k as long as the pattern matches, i.e. as long as s[l+k] bit string can be reconstructed by s[i+k] bit string. Note that the matched pattern can "run over" l because the pattern starts copying itself (see LZ 76 paper). This is just what happens when you apply the cloning tool on photoshop to a region where you've already cloned...
            k=k+1

            if l+k>n: # if we reach the end of the string while matching, we need to add that to the tokens, and stop.
                c=c+1
                stop=1



    # a la Lempel and Ziv (IEEE trans inf theory it-22, 75 (1976),
    # h(n)=c(n)/b(n) where c(n) is the kolmogorov complexity
    # and h(n) is a normalised measure of complexity.
    complexity=c;

    #b=n*1.0/np.log2(n)
    #complexity=c/b;

    return complexity


def calc_KC(s):
    L = len(s)
    if s == '0'*L or s == '1'*L:
        return np.log2(L)
    else:
        return np.log2(L)*(KC_LZ(s)+KC_LZ(s[::-1]))/2.0
