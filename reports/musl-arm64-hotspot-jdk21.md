---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-15 05:55:36 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (3 unique values: 41-51 cores)</summary>

```
1792057839 41
1792057844 41
1792057849 46
1792057854 46
1792057859 51
1792057864 51
1792057869 51
1792057874 51
1792057879 51
1792057884 51
1792057889 51
1792057894 51
1792057899 51
1792057904 51
1792057909 51
1792057914 51
1792057919 51
1792057924 51
1792057929 51
1792057934 51
```
</details>

---

