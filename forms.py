from django import forms
from .models import MovieOrAnime

class MovieOrAnimeForm(forms.ModelForm):
    class Meta:
        model = MovieOrAnime
        fields = ['favorite_order', 'title_th', 'title_en', 'seasons', 'viewing_platform']
        widgets = {
            'favorite_order': forms.NumberInput(attrs={'class': 'form-control', 'placeholder': 'ลำดับที่ชอบ'}),
            'title_th': forms.TextInput(attrs={'class': 'form-control', 'placeholder': 'ชื่อเรื่องภาษาไทย'}),
            'title_en': forms.TextInput(attrs={'class': 'form-control', 'placeholder': 'ชื่อเรื่องภาษาอังกฤษ'}),
            'seasons': forms.NumberInput(attrs={'class': 'form-control', 'placeholder': 'จำนวนซีซั่น'}),
            'viewing_platform': forms.TextInput(attrs={'class': 'form-control', 'placeholder': 'ช่องทางการรับชม'}),
        }

    def clean_favorite_order(self):
        value = self.cleaned_data['favorite_order']
        if value <= 0:
            raise forms.ValidationError('ลำดับที่ชอบต้องมีค่ามากกว่า 0')
        return value

    def clean_seasons(self):
        value = self.cleaned_data['seasons']
        if value <= 0:
            raise forms.ValidationError('จำนวนซีซั่นต้องมีค่ามากกว่า 0')
        return value
