---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 11:31:11 EST

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
| CPU Cores (start) | 65 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 8 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 757 |
| Sample Rate | 12.62/sec |
| Health Score | 789% |
| Threads | 9 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (3 unique values: 65-69 cores)</summary>

```
1795105559 65
1795105564 65
1795105569 65
1795105574 65
1795105579 67
1795105584 67
1795105589 67
1795105594 67
1795105599 67
1795105604 67
1795105609 67
1795105614 67
1795105619 67
1795105624 67
1795105629 67
1795105635 67
1795105640 67
1795105645 67
1795105650 67
1795105655 69
```
</details>

---

