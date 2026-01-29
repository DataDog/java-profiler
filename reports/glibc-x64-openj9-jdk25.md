---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-01-29 08:17:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 650 |
| Sample Rate | 21.67/sec |
| Health Score | 1354% |
| Threads | 10 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 824 |
| Sample Rate | 27.47/sec |
| Health Score | 1717% |
| Threads | 12 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (2 unique values: 81-86 cores)</summary>

```
1769692282 86
1769692287 86
1769692292 86
1769692297 86
1769692302 86
1769692307 86
1769692312 86
1769692317 86
1769692322 86
1769692327 81
1769692332 81
1769692337 81
1769692342 81
1769692347 81
1769692352 81
1769692357 81
1769692362 81
1769692367 81
1769692372 81
1769692377 81
```
</details>

---

