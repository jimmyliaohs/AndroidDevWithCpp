package com.glumes.androidcppsolib.ui

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.support.v7.widget.LinearLayoutManager
import com.glumes.androidcppsolib.R
import com.glumes.androidcppsolib.base.BaseActivity
import com.glumes.androidcppsolib.utils.NATIVE_INT_ARRAY
import com.glumes.androidcppsolib.utils.NATIVE_STRING
import com.glumes.androidcppsolib.viewholder.SampleBinder
import com.glumes.androidcppsolib.viewholder.SampleModel
import com.glumes.databindingadapter.DataBindingAdapter
import com.glumes.databindingadapter.Items
import kotlinx.android.synthetic.main.activity_base.*

class NativeOperationActivity : BaseActivity() {

    val items = Items()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        initRecyclerView()

        initData()

    }


    private fun initRecyclerView() {
        val layoutManager = LinearLayoutManager(this)
        layoutManager.orientation = LinearLayoutManager.VERTICAL
        mRecyclerView.layoutManager = layoutManager
        val mAdapter = DataBindingAdapter()

        mAdapter.map(SampleModel::class.java, SampleBinder()).setItems(items)

        mRecyclerView.adapter = mAdapter

    }


    private fun initData() {
        items.add(SampleModel("getNativeString", NATIVE_STRING))
        items.add(SampleModel("getNativeIntArray", NATIVE_INT_ARRAY))
        items.add(SampleModel("a"))
        items.add(SampleModel("a"))
        items.add(SampleModel("a"))
        items.add(SampleModel("a"))
    }
}
