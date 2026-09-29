---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-29 07:07:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 176 |
| Sample Rate | 2.93/sec |
| Health Score | 183% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 158 |
| Sample Rate | 2.63/sec |
| Health Score | 164% |
| Threads | 12 |
| Allocations | 30 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1790679799 38
1790679804 38
1790679809 38
1790679814 38
1790679819 38
1790679824 38
1790679829 38
1790679834 38
1790679839 38
1790679844 43
1790679850 43
1790679855 43
1790679860 43
1790679865 43
1790679870 43
1790679875 43
1790679880 43
1790679885 43
1790679890 43
1790679895 43
```
</details>

---

