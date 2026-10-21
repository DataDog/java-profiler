---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-21 16:37:07 EDT

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
| CPU Cores (start) | 15 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 448 |
| Sample Rate | 7.47/sec |
| Health Score | 467% |
| Threads | 8 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 689 |
| Sample Rate | 11.48/sec |
| Health Score | 718% |
| Threads | 9 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (4 unique values: 15-48 cores)</summary>

```
1792614672 15
1792614677 15
1792614682 15
1792614687 48
1792614692 48
1792614697 27
1792614702 27
1792614707 27
1792614712 27
1792614717 18
1792614722 18
1792614727 18
1792614732 18
1792614737 18
1792614742 18
1792614747 18
1792614752 18
1792614757 18
1792614762 18
1792614767 18
```
</details>

---

