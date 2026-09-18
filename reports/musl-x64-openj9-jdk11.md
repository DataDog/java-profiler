---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 11:09:01 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 720 |
| Sample Rate | 12.00/sec |
| Health Score | 750% |
| Threads | 10 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (3 unique values: 41-67 cores)</summary>

```
1789743399 41
1789743404 41
1789743409 41
1789743414 43
1789743419 43
1789743424 43
1789743429 43
1789743434 43
1789743439 43
1789743444 43
1789743449 43
1789743454 43
1789743459 43
1789743464 43
1789743469 43
1789743475 43
1789743480 43
1789743485 43
1789743490 43
1789743495 67
```
</details>

---

