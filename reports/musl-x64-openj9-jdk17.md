---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-02-04 10:23:40 EST

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 630 |
| Sample Rate | 10.50/sec |
| Health Score | 656% |
| Threads | 9 |
| Allocations | 330 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 953 |
| Sample Rate | 15.88/sec |
| Health Score | 993% |
| Threads | 11 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (6 unique values: 65-77 cores)</summary>

```
1770218262 75
1770218267 77
1770218272 77
1770218277 72
1770218282 72
1770218287 72
1770218292 72
1770218297 70
1770218302 70
1770218307 70
1770218312 70
1770218317 70
1770218322 70
1770218327 70
1770218332 70
1770218337 70
1770218342 70
1770218347 70
1770218352 68
1770218357 68
```
</details>

---

