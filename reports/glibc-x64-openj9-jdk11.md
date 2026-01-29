---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-01-29 08:17:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 650 |
| Sample Rate | 21.67/sec |
| Health Score | 1354% |
| Threads | 8 |
| Allocations | 330 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 698 |
| Sample Rate | 23.27/sec |
| Health Score | 1454% |
| Threads | 9 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1769692272 32
1769692277 32
1769692282 32
1769692287 32
1769692292 32
1769692297 32
1769692302 32
1769692307 32
1769692312 32
1769692317 32
1769692322 32
1769692327 32
1769692332 32
1769692337 32
1769692342 32
1769692347 32
1769692352 32
1769692358 32
1769692363 32
1769692368 32
```
</details>

---

