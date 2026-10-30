---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-30 09:45:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 12 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 8 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 640 |
| Sample Rate | 10.67/sec |
| Health Score | 667% |
| Threads | 9 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (2 unique values: 10-12 cores)</summary>

```
1793367640 12
1793367645 12
1793367650 12
1793367656 12
1793367661 12
1793367666 12
1793367671 12
1793367676 12
1793367681 12
1793367686 12
1793367691 12
1793367696 12
1793367701 12
1793367706 12
1793367711 12
1793367716 12
1793367721 12
1793367726 10
1793367731 10
1793367736 10
```
</details>

---

