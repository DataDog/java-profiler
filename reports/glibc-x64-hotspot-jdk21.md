---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-26 11:06:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 446 |
| Sample Rate | 7.43/sec |
| Health Score | 464% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 9 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1793026820 28
1793026825 28
1793026830 28
1793026835 28
1793026840 28
1793026845 30
1793026850 30
1793026855 30
1793026860 30
1793026865 28
1793026870 28
1793026875 28
1793026880 28
1793026885 28
1793026890 28
1793026895 28
1793026900 28
1793026905 28
1793026910 28
1793026915 28
```
</details>

---

