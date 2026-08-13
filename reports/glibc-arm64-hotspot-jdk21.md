---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-13 15:42:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 12 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 803 |
| Sample Rate | 13.38/sec |
| Health Score | 836% |
| Threads | 11 |
| Allocations | 435 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1786649894 64
1786649899 64
1786649904 64
1786649909 64
1786649914 64
1786649919 64
1786649924 64
1786649929 64
1786649934 64
1786649939 64
1786649944 64
1786649949 64
1786649954 64
1786649959 64
1786649964 64
1786649969 64
1786649974 59
1786649979 59
1786649984 59
1786649989 59
```
</details>

---

