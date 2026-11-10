---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-10 15:03:07 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 249 |
| Sample Rate | 4.15/sec |
| Health Score | 259% |
| Threads | 10 |
| Allocations | 129 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 9 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794340569 51
1794340574 51
1794340579 51
1794340584 51
1794340589 51
1794340594 51
1794340599 51
1794340604 51
1794340609 51
1794340614 46
1794340619 46
1794340624 46
1794340629 46
1794340634 46
1794340639 46
1794340644 46
1794340649 46
1794340654 46
1794340659 46
1794340664 46
```
</details>

---

