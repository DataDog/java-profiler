---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 05:30:24 EST

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
| CPU Cores (start) | 37 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 441 |
| Sample Rate | 7.35/sec |
| Health Score | 459% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 622 |
| Sample Rate | 10.37/sec |
| Health Score | 648% |
| Threads | 11 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (4 unique values: 37-75 cores)</summary>

```
1794997491 37
1794997496 37
1794997501 37
1794997506 37
1794997511 37
1794997516 37
1794997521 37
1794997526 57
1794997531 57
1794997536 57
1794997541 57
1794997546 57
1794997551 66
1794997556 66
1794997561 66
1794997566 66
1794997571 75
1794997576 75
1794997581 75
1794997586 75
```
</details>

---

