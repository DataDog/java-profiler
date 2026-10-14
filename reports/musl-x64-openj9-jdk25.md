---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-14 12:40:14 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 423 |
| Sample Rate | 7.05/sec |
| Health Score | 441% |
| Threads | 8 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 513 |
| Sample Rate | 8.55/sec |
| Health Score | 534% |
| Threads | 8 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1791995649 30
1791995654 30
1791995659 30
1791995664 30
1791995669 30
1791995674 30
1791995679 30
1791995684 32
1791995689 32
1791995694 32
1791995699 32
1791995704 32
1791995709 32
1791995714 32
1791995719 32
1791995724 32
1791995729 32
1791995734 32
1791995739 32
1791995744 32
```
</details>

---

