---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-10 20:36:48 EST

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 701 |
| Sample Rate | 11.68/sec |
| Health Score | 730% |
| Threads | 10 |
| Allocations | 609 |

<details>
<summary>CPU Timeline (4 unique values: 62-82 cores)</summary>

```
1794360740 73
1794360745 73
1794360750 73
1794360755 73
1794360760 73
1794360765 75
1794360770 75
1794360775 75
1794360780 75
1794360785 75
1794360790 75
1794360795 75
1794360800 75
1794360805 75
1794360810 75
1794360815 75
1794360820 75
1794360825 73
1794360830 73
1794360835 82
```
</details>

---

