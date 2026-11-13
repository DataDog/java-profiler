---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-13 11:59:07 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 452 |
| Sample Rate | 7.53/sec |
| Health Score | 471% |
| Threads | 9 |
| Allocations | 344 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 579 |
| Sample Rate | 9.65/sec |
| Health Score | 603% |
| Threads | 11 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (6 unique values: 90-96 cores)</summary>

```
1794588782 91
1794588787 91
1794588792 91
1794588798 91
1794588803 93
1794588808 93
1794588813 93
1794588818 93
1794588823 93
1794588828 93
1794588833 93
1794588838 93
1794588843 96
1794588848 96
1794588853 94
1794588858 94
1794588863 94
1794588868 94
1794588873 94
1794588878 94
```
</details>

---

