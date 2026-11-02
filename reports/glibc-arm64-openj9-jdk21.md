---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-02 06:14:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 12 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 262 |
| Sample Rate | 4.37/sec |
| Health Score | 273% |
| Threads | 11 |
| Allocations | 119 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1793617784 51
1793617789 51
1793617794 51
1793617799 51
1793617804 51
1793617809 51
1793617814 51
1793617819 51
1793617824 51
1793617829 51
1793617834 51
1793617839 51
1793617844 51
1793617849 51
1793617854 51
1793617859 51
1793617864 51
1793617869 51
1793617874 51
1793617879 51
```
</details>

---

