---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-28 14:02:38 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 393 |
| Sample Rate | 6.55/sec |
| Health Score | 409% |
| Threads | 13 |
| Allocations | 169 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787939898 64
1787939903 64
1787939908 64
1787939913 64
1787939918 64
1787939923 64
1787939928 64
1787939933 64
1787939938 64
1787939943 64
1787939948 64
1787939953 64
1787939958 64
1787939963 64
1787939968 64
1787939973 64
1787939978 64
1787939983 64
1787939988 64
1787939993 64
```
</details>

---

