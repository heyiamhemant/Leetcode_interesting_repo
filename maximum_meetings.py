def maximumMeetings():
    # Write your Code here
    start = [1, 3, 0, 5, 8, 5]
    end = [2, 4, 6, 7, 9, 9]
    meetings = [(start[i], end[i], i) for i in range(len(start))]
    meetings.sort(key=lambda x: x[1])
    result = []
    limit = -1
    for it in meetings:
        if it[0] > limit:
            result.append(it[2])
            limit = it[1]
    print(result)


# driver
maximumMeetings()
