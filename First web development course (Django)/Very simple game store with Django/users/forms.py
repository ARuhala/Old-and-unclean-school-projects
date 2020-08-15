# users/forms.py
from django import forms
from django.contrib.auth.forms import UserCreationForm, UserChangeForm
from .models import CustomUser

class CustomUserCreationForm(UserCreationForm):

    class Meta(UserCreationForm.Meta):
        model = CustomUser
        fields = ('username',)

class CustomUserChangeForm(UserChangeForm):

    class Meta:
        model = CustomUser
        fields = UserChangeForm.Meta.fields

class AddGameForm(forms.Form):
    url = forms.URLField(label='Game url')
    price = forms.IntegerField(label='Price', min_value=0)
    name = forms.CharField(label="Descriptive name", max_length=255)

class DelGameForm(forms.Form):
    url = forms.URLField(label='Game url')

class PlayGameForm(forms.Form):
    id = forms.UUIDField(label='Game ID')


class LoanGameForm(forms.Form):
    id = forms.UUIDField(label='Game ID')
