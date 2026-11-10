---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-10 10:21:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 10 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 593 |
| Sample Rate | 9.88/sec |
| Health Score | 618% |
| Threads | 11 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (5 unique values: 21-26 cores)</summary>

```
1794323799 22
1794323804 22
1794323809 22
1794323814 22
1794323819 21
1794323824 21
1794323829 25
1794323834 25
1794323839 25
1794323844 25
1794323849 25
1794323854 25
1794323859 25
1794323864 25
1794323869 25
1794323874 25
1794323879 25
1794323884 25
1794323889 25
1794323894 25
```
</details>

---

