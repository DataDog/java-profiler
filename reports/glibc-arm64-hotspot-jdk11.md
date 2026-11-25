---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 10:08:08 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 386 |
| Sample Rate | 6.43/sec |
| Health Score | 402% |
| Threads | 13 |
| Allocations | 177 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1017 |
| Sample Rate | 16.95/sec |
| Health Score | 1059% |
| Threads | 9 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1795618886 43
1795618891 43
1795618896 43
1795618901 43
1795618906 48
1795618911 48
1795618916 48
1795618921 48
1795618926 48
1795618931 48
1795618936 48
1795618941 48
1795618946 48
1795618951 48
1795618956 48
1795618961 48
1795618966 48
1795618971 48
1795618976 48
1795618981 48
```
</details>

---

