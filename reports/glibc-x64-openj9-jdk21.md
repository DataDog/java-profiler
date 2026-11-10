---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-10 09:09:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 11 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (4 unique values: 55-67 cores)</summary>

```
1794319466 65
1794319471 67
1794319476 67
1794319481 67
1794319486 67
1794319491 67
1794319496 67
1794319501 63
1794319506 63
1794319511 63
1794319516 63
1794319521 63
1794319526 63
1794319531 63
1794319536 63
1794319541 63
1794319546 67
1794319551 67
1794319556 67
1794319561 67
```
</details>

---

