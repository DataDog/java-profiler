---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 05:59:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 442 |
| Sample Rate | 7.37/sec |
| Health Score | 461% |
| Threads | 9 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 10 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (6 unique values: 65-94 cores)</summary>

```
1794480764 68
1794480769 68
1794480774 65
1794480779 65
1794480784 65
1794480789 65
1794480794 65
1794480799 65
1794480804 86
1794480809 86
1794480814 86
1794480819 86
1794480824 86
1794480829 86
1794480834 86
1794480839 86
1794480844 86
1794480849 86
1794480854 86
1794480859 86
```
</details>

---

