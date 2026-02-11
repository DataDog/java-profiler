---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-11 11:58:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 8 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 961 |
| Sample Rate | 16.02/sec |
| Health Score | 1001% |
| Threads | 11 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (3 unique values: 75-80 cores)</summary>

```
1770828667 80
1770828672 80
1770828677 80
1770828682 80
1770828687 80
1770828692 76
1770828697 76
1770828702 76
1770828707 76
1770828712 76
1770828717 76
1770828722 75
1770828727 75
1770828732 75
1770828737 75
1770828742 75
1770828747 75
1770828752 75
1770828757 75
1770828762 75
```
</details>

---

