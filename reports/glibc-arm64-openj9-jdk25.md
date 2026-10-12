---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-12 09:25:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 207 |
| Sample Rate | 3.45/sec |
| Health Score | 216% |
| Threads | 9 |
| Allocations | 159 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 11 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (5 unique values: 41-48 cores)</summary>

```
1791811267 45
1791811272 45
1791811277 45
1791811282 45
1791811287 48
1791811292 48
1791811297 48
1791811302 48
1791811307 43
1791811312 43
1791811317 43
1791811322 43
1791811327 43
1791811332 43
1791811337 43
1791811342 43
1791811347 43
1791811352 43
1791811357 41
1791811362 41
```
</details>

---

