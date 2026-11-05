---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-05 11:16:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 10 |
| Allocations | 330 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 10 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (4 unique values: 78-92 cores)</summary>

```
1793895017 78
1793895022 78
1793895027 90
1793895032 90
1793895037 90
1793895042 90
1793895047 90
1793895052 90
1793895057 90
1793895062 92
1793895067 92
1793895072 92
1793895077 92
1793895082 92
1793895087 92
1793895092 88
1793895097 88
1793895102 88
1793895107 88
1793895112 88
```
</details>

---

