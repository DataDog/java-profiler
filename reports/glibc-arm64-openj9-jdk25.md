---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 15:27:12 EST

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
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 11 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (4 unique values: 26-48 cores)</summary>

```
1794428606 43
1794428612 43
1794428617 43
1794428622 43
1794428627 43
1794428632 26
1794428637 26
1794428642 26
1794428647 26
1794428652 31
1794428657 31
1794428662 31
1794428667 31
1794428672 31
1794428677 31
1794428682 31
1794428687 31
1794428692 31
1794428697 31
1794428702 31
```
</details>

---

