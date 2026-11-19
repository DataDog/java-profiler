---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-19 05:46:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 513 |
| Sample Rate | 8.55/sec |
| Health Score | 534% |
| Threads | 9 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 10.47/sec |
| Health Score | 654% |
| Threads | 10 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (5 unique values: 69-79 cores)</summary>

```
1795085014 71
1795085019 71
1795085024 71
1795085029 71
1795085034 71
1795085039 71
1795085044 71
1795085049 69
1795085055 69
1795085060 69
1795085065 69
1795085070 69
1795085075 69
1795085080 69
1795085085 69
1795085090 69
1795085095 69
1795085100 69
1795085105 69
1795085110 79
```
</details>

---

