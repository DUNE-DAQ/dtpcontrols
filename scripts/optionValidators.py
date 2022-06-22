import click
# ------------------------------------------------------------------------------
def validate_link_ids(ctx, param, value):
    first, last = 0, ctx.obj.mConfigInfo['n_links']
    return _validate_range_impl(value, first, last)


# ------------------------------------------------------------------------------
def validate_proc_ids(ctx, param, value):
    first, last = 0, ctx.obj.mConfigInfo['n_port']
    return _validate_range_impl(value, first, last)


# ------------------------------------------------------------------------------
def validate_chan_ids(ctx, param, value):
    first, last = 0, ctx.obj.mConfigInfo['n_mux']
    return _validate_range_impl(value, first, last)


# ------------------------------------------------------------------------------
def _validate_range_impl(value, first, last):
        if value is None:
            return None

        if value == 'all':
            return list(range(first, last))
        elif value == 'none':
            return []

        if not value[0].isdigit():
            raise click.ClickException('Malformed option (comma separated list expected): %s' % value)

        _sep  = ','
        _dash = '-'

        numbers = []
        items = value.split(_sep)
        for item in items:
            nums = item.split(_dash)
            if len(nums) == 1:
                # single number
                numbers.append(int(item))
            elif len(nums) == 2:
                i = int(nums[0])
                j = int(nums[1])
                if i > j:
                    raise click.ClickException('Invalid interval '+item)
                numbers.extend(list(range(i, j+1)))
            else:
                raise click.ClickException('Malformed option (comma separated list expected): %s' % value)

        out_of_range = [n for n in numbers if (n < first or n >= last)]
        if any(out_of_range):
            raise click.ClickException('Values out of range %s-%s: %s' % (first, last, out_of_range))

        return numbers
