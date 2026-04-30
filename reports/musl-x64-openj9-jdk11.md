---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-30 14:54:49 EDT

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 603 |
| Sample Rate | 10.05/sec |
| Health Score | 628% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1039 |
| Sample Rate | 17.32/sec |
| Health Score | 1082% |
| Threads | 10 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (3 unique values: 78-96 cores)</summary>

```
1777575015 78
1777575020 78
1777575025 78
1777575030 78
1777575035 78
1777575040 78
1777575045 78
1777575050 78
1777575055 78
1777575060 78
1777575065 78
1777575070 78
1777575075 78
1777575080 96
1777575085 96
1777575090 96
1777575095 91
1777575100 91
1777575105 91
1777575110 91
```
</details>

---

