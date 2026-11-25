---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 10:08:11 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 45 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (2 unique values: 33-44 cores)</summary>

```
1795618917 33
1795618922 33
1795618927 33
1795618932 33
1795618937 33
1795618942 44
1795618947 44
1795618952 44
1795618957 44
1795618962 44
1795618967 44
1795618972 44
1795618977 44
1795618982 44
1795618987 44
1795618992 44
1795618997 44
1795619002 44
1795619007 44
1795619012 44
```
</details>

---

