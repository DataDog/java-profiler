---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-13 00:57:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 12 |
| Allocations | 209 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 41 |
| Sample Rate | 0.68/sec |
| Health Score | 42% |
| Threads | 11 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (2 unique values: 51-56 cores)</summary>

```
1786596784 51
1786596789 51
1786596794 51
1786596799 51
1786596804 51
1786596809 51
1786596814 51
1786596819 51
1786596824 51
1786596829 51
1786596834 51
1786596839 51
1786596844 56
1786596849 56
1786596854 56
1786596859 56
1786596864 56
1786596869 56
1786596874 56
1786596879 56
```
</details>

---

