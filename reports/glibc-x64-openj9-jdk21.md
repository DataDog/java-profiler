---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 13:57:01 EST

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 751 |
| Sample Rate | 12.52/sec |
| Health Score | 782% |
| Threads | 11 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (4 unique values: 76-82 cores)</summary>

```
1794509580 82
1794509585 82
1794509590 82
1794509595 82
1794509600 82
1794509605 82
1794509610 82
1794509615 82
1794509620 82
1794509626 82
1794509631 82
1794509636 82
1794509641 80
1794509646 80
1794509651 78
1794509656 78
1794509661 76
1794509666 76
1794509671 76
1794509676 78
```
</details>

---

