---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-06 10:50:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 11 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 695 |
| Sample Rate | 11.58/sec |
| Health Score | 724% |
| Threads | 13 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (6 unique values: 53-64 cores)</summary>

```
1770392818 62
1770392823 64
1770392828 64
1770392833 64
1770392838 59
1770392843 59
1770392848 59
1770392853 59
1770392858 59
1770392863 59
1770392868 59
1770392873 59
1770392878 59
1770392883 59
1770392888 57
1770392893 57
1770392898 57
1770392904 57
1770392909 53
1770392914 53
```
</details>

---

