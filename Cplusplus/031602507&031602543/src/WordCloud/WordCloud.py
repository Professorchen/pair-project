from wordcloud import WordCloud,ImageColorGenerator,STOPWORDS
import jieba
import matplotlib.pyplot as plt
from PIL import Image
import numpy as np 
 

text = open('result.txt','r', encoding='UTF-8').read()

cut_text = jieba.cut(text)
result = '/'.join(cut_text)

stopwords = set(STOPWORDS)

image = Image.open('fivestart.png')  
img = np.array(image) 
#词云的生成,字体的路径一定要写上不然会出现乱码 可以下载其他字体创新
wc = WordCloud(font_path = "C:\Windows\Fonts\STHUPO.ttf",background_color='white',max_font_size=150,mask=img) 
# WordCloud其他参数设置,random_state=42,max_words=2000,min_font_size=20
wc.generate(result)
#绘制文字的颜色以背景图颜色为参考  
image_color = ImageColorGenerator(img)
wc.recolor(color_func=image_color)  
#图片的展示 
plt.imshow(wc)
plt.axis("off")
# 像素点多少
plt.savefig("wordcloud3.png",dpi=300)
# plt.show()
