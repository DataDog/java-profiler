---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-23 20:34:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 957 |
| Sample Rate | 15.95/sec |
| Health Score | 997% |
| Threads | 10 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (2 unique values: 57-81 cores)</summary>

```
1790209779 57
1790209784 57
1790209789 57
1790209794 57
1790209799 57
1790209804 81
1790209809 81
1790209814 81
1790209819 81
1790209824 81
1790209829 81
1790209834 81
1790209839 81
1790209844 81
1790209849 81
1790209854 81
1790209859 81
1790209864 81
1790209869 81
1790209874 81
```
</details>

---

