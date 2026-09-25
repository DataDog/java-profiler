---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-25 10:31:17 EDT

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
| CPU Cores (end) | 88 |
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
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 994 |
| Sample Rate | 16.57/sec |
| Health Score | 1036% |
| Threads | 9 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (2 unique values: 70-80 cores)</summary>

```
1790346384 70
1790346389 70
1790346394 70
1790346399 70
1790346404 70
1790346409 70
1790346414 70
1790346419 70
1790346424 70
1790346429 70
1790346434 70
1790346439 70
1790346444 70
1790346449 70
1790346454 70
1790346459 70
1790346464 70
1790346469 70
1790346474 70
1790346479 70
```
</details>

---

