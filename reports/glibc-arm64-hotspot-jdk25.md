---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-24 04:38:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 11 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (3 unique values: 34-50 cores)</summary>

```
1790238872 34
1790238877 34
1790238882 34
1790238887 34
1790238892 34
1790238897 34
1790238902 34
1790238907 34
1790238912 34
1790238917 34
1790238922 34
1790238927 34
1790238932 34
1790238937 34
1790238942 34
1790238947 34
1790238952 34
1790238957 46
1790238962 46
1790238967 50
```
</details>

---

