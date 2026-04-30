---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-04-30 10:12:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 340 |
| Sample Rate | 5.67/sec |
| Health Score | 354% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 445 |
| Sample Rate | 7.42/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (8 unique values: 52-78 cores)</summary>

```
1777558049 52
1777558054 52
1777558059 52
1777558065 52
1777558070 57
1777558075 57
1777558080 57
1777558085 61
1777558090 61
1777558095 65
1777558100 65
1777558105 65
1777558110 63
1777558115 63
1777558120 64
1777558125 64
1777558130 64
1777558135 66
1777558140 66
1777558145 78
```
</details>

---

