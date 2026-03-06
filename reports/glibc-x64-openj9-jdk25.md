---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-06 04:52:17 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 386 |
| Sample Rate | 6.43/sec |
| Health Score | 402% |
| Threads | 10 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 688 |
| Sample Rate | 11.47/sec |
| Health Score | 717% |
| Threads | 12 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (6 unique values: 72-92 cores)</summary>

```
1772790361 72
1772790366 72
1772790371 72
1772790376 72
1772790381 76
1772790386 76
1772790391 76
1772790396 76
1772790401 76
1772790406 81
1772790411 81
1772790416 83
1772790421 83
1772790426 88
1772790431 88
1772790436 88
1772790441 88
1772790446 88
1772790451 88
1772790456 88
```
</details>

---

