package com.voicelab.android

import android.Manifest
import android.content.pm.PackageManager
import android.os.Bundle
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import com.voicelab.android.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {
    
    private lateinit var binding: ActivityMainBinding
    private var isProcessing = false
    
    companion object {
        private const val PERMISSION_REQUEST_CODE = 1001
        
        init {
            System.loadLibrary("voicelab_native")
        }
    }
    
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)
        
        // Initialize native audio engine
        initNativeAudio()
        
        // Setup UI
        setupUI()
        
        // Request audio permissions
        checkAndRequestPermissions()
    }
    
    private fun setupUI() {
        binding.versionText.text = "Native Version: ${getNativeVersion()}"
        
        binding.startButton.setOnClickListener {
            if (checkPermissions()) {
                toggleProcessing()
            } else {
                requestPermissions()
            }
        }
        
        binding.testButton.setOnClickListener {
            if (checkPermissions()) {
                val result = testNativeAudioProcessing()
                Toast.makeText(this, "Test Result: $result", Toast.LENGTH_SHORT).show()
            }
        }
    }
    
    private fun toggleProcessing() {
        isProcessing = !isProcessing
        if (isProcessing) {
            startNativeProcessing()
            binding.startButton.text = "Stop Processing"
            binding.statusText.text = "Status: Processing"
        } else {
            stopNativeProcessing()
            binding.startButton.text = "Start Processing"
            binding.statusText.text = "Status: Stopped"
        }
    }
    
    private fun checkPermissions(): Boolean {
        return ContextCompat.checkSelfPermission(
            this,
            Manifest.permission.RECORD_AUDIO
        ) == PackageManager.PERMISSION_GRANTED
    }
    
    private fun checkAndRequestPermissions() {
        if (!checkPermissions()) {
            requestPermissions()
        }
    }
    
    private fun requestPermissions() {
        ActivityCompat.requestPermissions(
            this,
            arrayOf(Manifest.permission.RECORD_AUDIO),
            PERMISSION_REQUEST_CODE
        )
    }
    
    override fun onRequestPermissionsResult(
        requestCode: Int,
        permissions: Array<out String>,
        grantResults: IntArray
    ) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults)
        if (requestCode == PERMISSION_REQUEST_CODE) {
            if (grantResults.isNotEmpty() && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                Toast.makeText(this, "Audio permission granted", Toast.LENGTH_SHORT).show()
            } else {
                Toast.makeText(this, "Audio permission denied", Toast.LENGTH_SHORT).show()
            }
        }
    }
    
    override fun onDestroy() {
        super.onDestroy()
        if (isProcessing) {
            stopNativeProcessing()
        }
        shutdownNativeAudio()
    }
    
    // Native methods
    private external fun initNativeAudio(): Boolean
    private external fun shutdownNativeAudio()
    private external fun startNativeProcessing(): Boolean
    private external fun stopNativeProcessing()
    private external fun testNativeAudioProcessing(): Float
    private external fun getNativeVersion(): String
}
