---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-21 07:29:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 736 |
| Sample Rate | 12.27/sec |
| Health Score | 767% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1000 |
| Sample Rate | 16.67/sec |
| Health Score | 1042% |
| Threads | 11 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (3 unique values: 49-65 cores)</summary>

```
1776770472 49
1776770477 49
1776770482 49
1776770487 49
1776770492 53
1776770497 53
1776770502 53
1776770507 53
1776770512 53
1776770517 53
1776770522 53
1776770527 65
1776770532 65
1776770537 65
1776770542 65
1776770547 65
1776770552 65
1776770557 65
1776770562 65
1776770568 65
```
</details>

---

