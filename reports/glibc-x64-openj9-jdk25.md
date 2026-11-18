---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 14:19:56 EST

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 725 |
| Sample Rate | 12.08/sec |
| Health Score | 755% |
| Threads | 12 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (2 unique values: 49-64 cores)</summary>

```
1795029381 49
1795029386 49
1795029391 49
1795029396 49
1795029401 49
1795029406 64
1795029411 64
1795029416 64
1795029421 64
1795029426 64
1795029431 64
1795029436 64
1795029442 64
1795029447 64
1795029452 64
1795029457 64
1795029462 64
1795029467 64
1795029472 64
1795029477 64
```
</details>

---

