---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-22 10:46:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 9 |
| Allocations | 424 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 265 |
| Sample Rate | 4.42/sec |
| Health Score | 276% |
| Threads | 12 |
| Allocations | 171 |

<details>
<summary>CPU Timeline (2 unique values: 49-64 cores)</summary>

```
1790087849 64
1790087854 64
1790087859 64
1790087864 64
1790087869 64
1790087874 64
1790087879 49
1790087884 49
1790087889 49
1790087894 49
1790087899 49
1790087904 49
1790087909 49
1790087914 49
1790087919 49
1790087924 49
1790087929 49
1790087934 49
1790087939 49
1790087944 49
```
</details>

---

