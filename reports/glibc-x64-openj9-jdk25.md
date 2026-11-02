---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-02 10:00:25 EST

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 395 |
| Sample Rate | 6.58/sec |
| Health Score | 411% |
| Threads | 8 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 9 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (2 unique values: 24-26 cores)</summary>

```
1793631339 26
1793631344 26
1793631349 26
1793631354 24
1793631359 24
1793631364 24
1793631369 24
1793631374 24
1793631379 26
1793631384 26
1793631389 26
1793631394 26
1793631399 26
1793631404 26
1793631409 26
1793631414 26
1793631419 26
1793631424 26
1793631429 26
1793631434 26
```
</details>

---

