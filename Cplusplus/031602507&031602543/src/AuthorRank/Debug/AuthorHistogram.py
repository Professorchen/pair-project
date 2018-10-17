import matplotlib.pyplot as plt

def autolabel(rects):
 for rect in rects:
  height = rect.get_height()
  plt.text(rect.get_x()+rect.get_width()/2.-0.2, 1.03*height, '%s' % float(height))
  
rf = open('AuthorRank.txt','r',encoding='UTF-8')
content = rf.readlines()
name_list = []
num_list = []
for x in content:
    Author = ""
    Count = ""
    flag1 = 0
    flag2 = 0
    for y in range(len(x)):
        if flag1 == 1:
            Author += x[y]
        if flag2 == 1:
            Count += x[y]
        if x[y] == ' ' and x[y-1] == ':':
            flag1 = 1
        if x[y] == ',':
            flag1 = 0
            flag2 = 1
    name_list.append(Author)
    num_list.append(int(Count))
plt.ylabel("Impact Factor")
plt.xlabel("Author Name")
plt.title(u"Author Rank")
fig = plt.bar(range(len(num_list)), num_list,width = 0.35,align='center',color = 'c',alpha=1)
plt.xticks(range(len(num_list)),name_list,size='small',rotation=30)
autolabel(fig)
plt.savefig("test.png")
plt.show()
