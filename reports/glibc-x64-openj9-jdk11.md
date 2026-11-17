---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-17 14:55:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 721 |
| Sample Rate | 12.02/sec |
| Health Score | 751% |
| Threads | 10 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (3 unique values: 70-74 cores)</summary>

```
1794945020 70
1794945025 70
1794945030 70
1794945035 70
1794945040 70
1794945045 70
1794945050 70
1794945055 70
1794945060 72
1794945065 72
1794945070 72
1794945075 72
1794945080 72
1794945085 74
1794945090 74
1794945095 74
1794945100 74
1794945105 72
1794945110 72
1794945115 72
```
</details>

---

