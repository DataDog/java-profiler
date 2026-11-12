---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 12:40:44 EST

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 391 |
| Sample Rate | 6.52/sec |
| Health Score | 407% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 10 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (2 unique values: 50-52 cores)</summary>

```
1794504910 52
1794504915 50
1794504920 50
1794504925 50
1794504930 50
1794504935 50
1794504940 50
1794504945 50
1794504950 50
1794504955 52
1794504960 52
1794504965 52
1794504970 52
1794504975 52
1794504980 52
1794504985 52
1794504990 52
1794504995 52
1794505000 52
1794505005 52
```
</details>

---

