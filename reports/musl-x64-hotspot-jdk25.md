---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-21 11:10:43 EDT

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 439 |
| Sample Rate | 7.32/sec |
| Health Score | 458% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 634 |
| Sample Rate | 10.57/sec |
| Health Score | 661% |
| Threads | 12 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (3 unique values: 70-74 cores)</summary>

```
1787324719 70
1787324724 70
1787324729 70
1787324734 70
1787324739 70
1787324744 70
1787324749 70
1787324754 72
1787324759 72
1787324764 72
1787324769 72
1787324774 74
1787324779 74
1787324784 74
1787324789 74
1787324794 74
1787324799 74
1787324804 74
1787324809 74
1787324814 74
```
</details>

---

