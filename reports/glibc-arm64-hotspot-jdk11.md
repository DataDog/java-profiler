---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-26 05:48:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 13 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 11 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 10 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (2 unique values: 13-18 cores)</summary>

```
1790415845 13
1790415850 13
1790415855 13
1790415860 13
1790415865 13
1790415870 13
1790415875 13
1790415880 13
1790415885 13
1790415890 13
1790415895 13
1790415900 13
1790415905 13
1790415910 13
1790415915 13
1790415920 13
1790415925 13
1790415930 18
1790415935 18
1790415940 18
```
</details>

---

