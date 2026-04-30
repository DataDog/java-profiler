---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-30 10:30:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 590 |
| Sample Rate | 9.83/sec |
| Health Score | 614% |
| Threads | 8 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 979 |
| Sample Rate | 16.32/sec |
| Health Score | 1020% |
| Threads | 11 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (3 unique values: 49-60 cores)</summary>

```
1777559051 49
1777559056 49
1777559061 49
1777559066 49
1777559071 49
1777559076 49
1777559081 49
1777559086 49
1777559091 49
1777559096 49
1777559101 49
1777559106 49
1777559111 51
1777559116 51
1777559121 51
1777559126 51
1777559131 51
1777559136 51
1777559141 51
1777559146 51
```
</details>

---

