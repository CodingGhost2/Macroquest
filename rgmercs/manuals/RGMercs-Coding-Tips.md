## Performance Tips

The following tips have been gathered from statements in #creators and other discord channels. We greatly appreciate all those who have offered great advice!

1. If you have nested variables such as: `${Variable1[${Variable2}, ${Variable3}]}` that are used regularly, store the result in a variable once and re-use to reduce CPU consumption.
2. Precedence for commands is: Alias > EQ Commands > Binds
3. Use SpawnCount's or check Spawn IDs to determine if a spawn exists rather than re-cast types to bools, this reduces the number of parser evaluations required