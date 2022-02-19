from future.utils import iteritems

kColorMap = {
    'black': 0,
    'red': 1,
    'green': 2,
    'yellow': 3,
    'blue': 4,
    'magenta': 5,
    'cyan': 6,
    'lightgray': 7,
    # 'orange': 215
}

# TODO: check 
for n, c in iteritems(kColorMap):
    # vars()['k' + n.capitalize()] = '\x1b[38;5;{}m'.format(c)
    vars()['k' + n.capitalize()] = '\x1b[3{}m'.format(c)

kReset = '\x1b[0m'
