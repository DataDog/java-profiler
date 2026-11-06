---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-05 20:23:04 EST

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 8 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 376 |
| Sample Rate | 6.27/sec |
| Health Score | 392% |
| Threads | 13 |
| Allocations | 145 |

<details>
<summary>CPU Timeline (1 unique values: 36-36 cores)</summary>

```
1793927874 36
1793927879 36
1793927884 36
1793927889 36
1793927894 36
1793927899 36
1793927904 36
1793927909 36
1793927914 36
1793927919 36
1793927924 36
1793927929 36
1793927934 36
1793927939 36
1793927944 36
1793927949 36
1793927954 36
1793927959 36
1793927964 36
1793927969 36
```
</details>

---

