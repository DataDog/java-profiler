---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-07 11:24:20 EDT

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 8 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1060 |
| Sample Rate | 17.67/sec |
| Health Score | 1104% |
| Threads | 11 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (5 unique values: 60-72 cores)</summary>

```
1778167176 67
1778167181 67
1778167186 67
1778167191 67
1778167196 60
1778167201 60
1778167206 60
1778167211 60
1778167216 65
1778167221 65
1778167226 65
1778167231 70
1778167236 70
1778167241 70
1778167246 70
1778167251 72
1778167256 72
1778167261 70
1778167266 70
1778167271 70
```
</details>

---

