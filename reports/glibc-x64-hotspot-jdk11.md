---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-24 13:05:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 8 |
| Allocations | 335 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 714 |
| Sample Rate | 11.90/sec |
| Health Score | 744% |
| Threads | 9 |
| Allocations | 552 |

<details>
<summary>CPU Timeline (2 unique values: 78-80 cores)</summary>

```
1795543258 80
1795543263 80
1795543268 78
1795543273 78
1795543278 78
1795543283 78
1795543288 78
1795543293 78
1795543298 78
1795543303 78
1795543308 80
1795543313 80
1795543318 80
1795543323 80
1795543328 80
1795543333 80
1795543338 80
1795543343 80
1795543348 80
1795543353 80
```
</details>

---

