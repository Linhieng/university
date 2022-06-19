
def experiment03():
    list = [['a', 8, 10], ['b', 1, 5], ['c', 4, 8], ['d', 1, 3], ['e', 6, 9], ['f', 2, 4], ['g', 4, 7], ['h', 1, 5], ['i', 6, 12]]
    job_sche = []
    list.sort(key=lambda x: x[2])
    for i in range(0, len(list)):
        if not job_sche:
            job_sche.append(list[i])
        else:
            if job_sche[-1][2] <= list[i][1]:
                job_sche.append(list[i])
    print(job_sche)

if __name__ == '__main__':
    experiment03()
