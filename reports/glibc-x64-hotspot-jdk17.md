---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-07 06:49:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 948 |
| Sample Rate | 15.80/sec |
| Health Score | 988% |
| Threads | 10 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (5 unique values: 80-91 cores)</summary>

```
1778150787 91
1778150792 91
1778150797 91
1778150802 91
1778150807 91
1778150812 91
1778150817 91
1778150822 87
1778150827 87
1778150832 87
1778150837 87
1778150842 83
1778150847 83
1778150852 83
1778150857 83
1778150862 83
1778150867 80
1778150872 80
1778150877 86
1778150882 86
```
</details>

---

