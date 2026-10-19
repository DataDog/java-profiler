---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-19 07:26:50 EDT

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 8 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 725 |
| Sample Rate | 12.08/sec |
| Health Score | 755% |
| Threads | 10 |
| Allocations | 543 |

<details>
<summary>CPU Timeline (2 unique values: 77-79 cores)</summary>

```
1792408960 79
1792408965 79
1792408970 79
1792408975 79
1792408980 79
1792408985 79
1792408990 79
1792408995 79
1792409000 79
1792409005 79
1792409010 79
1792409015 79
1792409020 77
1792409025 77
1792409030 77
1792409035 77
1792409040 77
1792409045 77
1792409050 77
1792409055 79
```
</details>

---

