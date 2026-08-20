---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-20 01:00:56 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 650 |
| Sample Rate | 10.83/sec |
| Health Score | 677% |
| Threads | 10 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (2 unique values: 42-44 cores)</summary>

```
1787201692 44
1787201697 44
1787201702 44
1787201707 44
1787201712 44
1787201717 44
1787201722 44
1787201727 44
1787201732 44
1787201737 44
1787201742 44
1787201747 44
1787201752 44
1787201757 44
1787201762 44
1787201767 44
1787201772 44
1787201777 44
1787201782 42
1787201787 42
```
</details>

---

