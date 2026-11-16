---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 09:37:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 9 |
| Allocations | 336 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 11 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (3 unique values: 72-76 cores)</summary>

```
1794839605 72
1794839610 72
1794839615 72
1794839620 72
1794839625 72
1794839630 74
1794839635 74
1794839640 76
1794839645 76
1794839650 76
1794839655 76
1794839660 76
1794839665 76
1794839670 76
1794839675 76
1794839680 76
1794839685 76
1794839690 76
1794839695 76
1794839700 76
```
</details>

---

