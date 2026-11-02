---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-02 10:00:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 438 |
| Sample Rate | 7.30/sec |
| Health Score | 456% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 728 |
| Sample Rate | 12.13/sec |
| Health Score | 758% |
| Threads | 11 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (4 unique values: 26-44 cores)</summary>

```
1793631309 42
1793631314 42
1793631319 42
1793631324 42
1793631329 42
1793631334 42
1793631339 42
1793631344 42
1793631349 42
1793631354 44
1793631359 44
1793631364 44
1793631369 44
1793631374 43
1793631379 43
1793631384 43
1793631389 43
1793631394 43
1793631399 43
1793631404 43
```
</details>

---

