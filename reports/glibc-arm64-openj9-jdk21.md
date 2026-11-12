---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 10:45:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 12 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (6 unique values: 23-44 cores)</summary>

```
1794497517 33
1794497522 33
1794497527 33
1794497532 33
1794497537 33
1794497542 33
1794497547 44
1794497552 44
1794497558 32
1794497563 32
1794497568 32
1794497573 23
1794497578 23
1794497583 23
1794497588 23
1794497593 23
1794497598 23
1794497603 24
1794497608 24
1794497613 24
```
</details>

---

