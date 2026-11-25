---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 16:28:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 8 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 7 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (3 unique values: 68-96 cores)</summary>

```
1795641754 68
1795641759 68
1795641764 68
1795641769 68
1795641774 68
1795641779 68
1795641784 68
1795641789 68
1795641794 68
1795641799 68
1795641805 68
1795641810 96
1795641815 96
1795641820 70
1795641825 70
1795641830 70
1795641835 70
1795641840 70
1795641845 70
1795641850 70
```
</details>

---

