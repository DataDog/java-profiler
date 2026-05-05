---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-05-05 08:22:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 177 |
| Sample Rate | 2.95/sec |
| Health Score | 184% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 750 |
| Sample Rate | 12.50/sec |
| Health Score | 781% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 47-57 cores)</summary>

```
1777983460 57
1777983465 57
1777983470 57
1777983475 57
1777983480 57
1777983485 57
1777983490 52
1777983495 52
1777983501 52
1777983506 52
1777983511 52
1777983516 52
1777983521 52
1777983526 52
1777983531 47
1777983536 47
1777983541 47
1777983546 47
1777983551 47
1777983556 47
```
</details>

---

