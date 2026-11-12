---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 05:59:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 760 |
| Sample Rate | 12.67/sec |
| Health Score | 792% |
| Threads | 9 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (4 unique values: 68-88 cores)</summary>

```
1794480755 68
1794480760 68
1794480765 68
1794480770 68
1794480775 68
1794480780 68
1794480785 68
1794480790 68
1794480795 68
1794480800 68
1794480805 68
1794480810 68
1794480815 88
1794480820 88
1794480825 88
1794480830 88
1794480835 88
1794480840 88
1794480845 88
1794480850 86
```
</details>

---

