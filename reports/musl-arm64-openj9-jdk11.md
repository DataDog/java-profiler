---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-20 06:48:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 10.30/sec |
| Health Score | 644% |
| Threads | 9 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787222590 48
1787222595 48
1787222600 48
1787222605 48
1787222610 48
1787222615 48
1787222620 48
1787222625 48
1787222630 48
1787222635 43
1787222640 43
1787222645 43
1787222650 43
1787222655 43
1787222660 43
1787222665 43
1787222670 43
1787222675 43
1787222680 43
1787222685 43
```
</details>

---

