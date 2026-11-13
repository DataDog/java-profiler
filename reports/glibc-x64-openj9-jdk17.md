---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 11:59:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 579 |
| Sample Rate | 9.65/sec |
| Health Score | 603% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 11 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (4 unique values: 32-52 cores)</summary>

```
1794588788 48
1794588793 50
1794588798 50
1794588803 50
1794588808 50
1794588813 48
1794588818 48
1794588823 32
1794588828 32
1794588833 32
1794588838 32
1794588843 32
1794588848 32
1794588853 32
1794588858 32
1794588863 32
1794588868 52
1794588873 52
1794588878 52
1794588883 52
```
</details>

---

