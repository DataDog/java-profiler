---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-22 14:20:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 365 |
| Sample Rate | 6.08/sec |
| Health Score | 380% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 7 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787422619 43
1787422624 48
1787422629 48
1787422634 48
1787422639 48
1787422644 48
1787422649 48
1787422654 48
1787422659 48
1787422664 48
1787422669 48
1787422674 48
1787422679 48
1787422684 48
1787422689 48
1787422694 48
1787422699 48
1787422704 48
1787422709 48
1787422714 48
```
</details>

---

