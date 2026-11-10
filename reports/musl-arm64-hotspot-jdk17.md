---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-10 10:21:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
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
| CPU Samples | 298 |
| Sample Rate | 4.97/sec |
| Health Score | 311% |
| Threads | 12 |
| Allocations | 123 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 359 |
| Sample Rate | 5.98/sec |
| Health Score | 374% |
| Threads | 12 |
| Allocations | 132 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794323798 43
1794323803 43
1794323808 43
1794323814 43
1794323819 43
1794323824 43
1794323829 43
1794323834 43
1794323839 43
1794323844 43
1794323849 43
1794323854 43
1794323859 43
1794323864 43
1794323869 48
1794323874 48
1794323879 48
1794323884 48
1794323889 48
1794323894 48
```
</details>

---

