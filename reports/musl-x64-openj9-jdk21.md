---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 02:28:28 EDT

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1012 |
| Sample Rate | 16.87/sec |
| Health Score | 1054% |
| Threads | 11 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (4 unique values: 88-92 cores)</summary>

```
1789712642 91
1789712647 91
1789712652 91
1789712657 91
1789712662 91
1789712667 91
1789712672 91
1789712677 88
1789712682 88
1789712687 88
1789712692 88
1789712697 88
1789712702 88
1789712707 88
1789712712 88
1789712717 88
1789712722 88
1789712727 88
1789712732 90
1789712737 90
```
</details>

---

