---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-15 08:44:40 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 684 |
| Sample Rate | 11.40/sec |
| Health Score | 712% |
| Threads | 9 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (3 unique values: 53-96 cores)</summary>

```
1778848644 53
1778848649 53
1778848654 53
1778848659 53
1778848664 53
1778848669 53
1778848674 53
1778848679 53
1778848684 53
1778848689 53
1778848694 53
1778848699 53
1778848704 53
1778848709 53
1778848714 53
1778848719 53
1778848724 53
1778848729 53
1778848734 96
1778848739 96
```
</details>

---

