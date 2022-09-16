#!/usr/bin/env python



import click
import json

from rich import print as rprint
from rich.console import Console

console = Console()

@click.command()
@click.argument("info_file",type=click.Path(exists=True))
def cli(info_file):
    rprint("[red]Hello[/red] [green]World[/green]")

    with open(info_file) as f:
        l = f.readlines()

    ll = l[-1]

    del l

    d = json.loads(ll)

    rprint(d)




if __name__ == '__main__':
    cli()
