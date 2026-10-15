---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-15 03:56:31 EDT

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
| CPU Cores (start) | 15 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 375 |
| Sample Rate | 6.25/sec |
| Health Score | 391% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 554 |
| Sample Rate | 9.23/sec |
| Health Score | 577% |
| Threads | 9 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (2 unique values: 15-17 cores)</summary>

```
1792050750 15
1792050755 15
1792050760 15
1792050765 15
1792050770 15
1792050775 17
1792050780 17
1792050785 17
1792050790 17
1792050795 17
1792050800 17
1792050805 17
1792050810 17
1792050815 15
1792050820 15
1792050825 15
1792050830 15
1792050835 15
1792050840 15
1792050845 15
```
</details>

---

