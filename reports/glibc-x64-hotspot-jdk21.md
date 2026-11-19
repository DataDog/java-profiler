---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-19 12:10:54 EST

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
| CPU Cores (start) | 20 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 705 |
| Sample Rate | 11.75/sec |
| Health Score | 734% |
| Threads | 10 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (3 unique values: 17-42 cores)</summary>

```
1795108003 20
1795108008 20
1795108013 42
1795108018 42
1795108023 42
1795108028 42
1795108033 17
1795108038 17
1795108043 17
1795108048 17
1795108053 17
1795108058 17
1795108063 17
1795108068 17
1795108073 17
1795108078 17
1795108083 17
1795108088 17
1795108093 17
1795108098 17
```
</details>

---

