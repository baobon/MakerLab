package bao.bon.gen2_controller.IntroView;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.viewpager.widget.PagerAdapter;

import org.w3c.dom.Text;

import java.util.List;

import bao.bon.gen2_controller.R;

public class IntroViewPageAdapter extends PagerAdapter {

    Context mContext;
    List<ScreenItem> mListScreenItem;

    public IntroViewPageAdapter(Context mContext, List<ScreenItem> mListScreenItem) {
        this.mContext = mContext;
        this.mListScreenItem = mListScreenItem;
    }

    @NonNull
    @Override
    public Object instantiateItem(@NonNull ViewGroup container, int position) {
//        return super.instantiateItem(container, position);
        LayoutInflater inflater = (LayoutInflater) mContext.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        View layoutScreen = inflater.inflate(R.layout.layout_screen,null);
        ImageView imgSlide = layoutScreen.findViewById(R.id.imageView_intro);
        TextView tittle = layoutScreen.findViewById(R.id.textView_intro_titlle);
        TextView description = layoutScreen.findViewById(R.id.textView_into_desciption);
        tittle.setText(mListScreenItem.get(position).getTittle());
        description.setText(mListScreenItem.get(position).getDescription());
        imgSlide.setImageResource(mListScreenItem.get(position).getScreenimg());

        container.addView(layoutScreen);
        return layoutScreen;
    }

    @Override
    public int getCount() {
        return mListScreenItem.size();
    }

    @Override
    public boolean isViewFromObject(@NonNull View view, @NonNull Object object) {
        return view == object;
    }

    @Override
    public void destroyItem(@NonNull ViewGroup container, int position, @NonNull Object object) {
//        super.destroyItem(container, position, object);
        container.removeView((View) object);
    }
}
