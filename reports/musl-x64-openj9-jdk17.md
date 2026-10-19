---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-19 07:26:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 13 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 472 |
| Sample Rate | 7.87/sec |
| Health Score | 492% |
| Threads | 8 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 718 |
| Sample Rate | 11.97/sec |
| Health Score | 748% |
| Threads | 8 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (2 unique values: 13-17 cores)</summary>

```
1792408948 13
1792408953 13
1792408958 17
1792408963 17
1792408968 17
1792408973 17
1792408978 17
1792408983 17
1792408988 17
1792408993 17
1792408998 17
1792409003 17
1792409008 17
1792409013 17
1792409018 17
1792409023 17
1792409028 17
1792409033 17
1792409038 17
1792409043 17
```
</details>

---

