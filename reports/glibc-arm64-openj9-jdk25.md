---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 06:36:01 EST

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 8 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 10 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (3 unique values: 26-51 cores)</summary>

```
1795001555 26
1795001560 26
1795001565 26
1795001570 26
1795001575 26
1795001580 26
1795001585 26
1795001590 51
1795001595 51
1795001600 51
1795001605 39
1795001610 39
1795001615 39
1795001620 39
1795001625 39
1795001630 39
1795001635 39
1795001640 39
1795001645 39
1795001650 39
```
</details>

---

