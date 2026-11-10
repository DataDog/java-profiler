---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-10 10:22:22 EST

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
| CPU Samples | 593 |
| Sample Rate | 9.88/sec |
| Health Score | 618% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 707 |
| Sample Rate | 11.78/sec |
| Health Score | 736% |
| Threads | 11 |
| Allocations | 433 |

<details>
<summary>CPU Timeline (4 unique values: 68-78 cores)</summary>

```
1794323804 68
1794323809 70
1794323814 70
1794323819 70
1794323824 70
1794323829 70
1794323834 70
1794323839 70
1794323844 70
1794323850 70
1794323855 70
1794323860 70
1794323865 70
1794323870 75
1794323875 75
1794323880 75
1794323885 75
1794323890 75
1794323895 75
1794323900 75
```
</details>

---

