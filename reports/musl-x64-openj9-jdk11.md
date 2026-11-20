---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-20 13:41:33 EST

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
| CPU Cores (start) | 11 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 8 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 694 |
| Sample Rate | 11.57/sec |
| Health Score | 723% |
| Threads | 9 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (3 unique values: 11-32 cores)</summary>

```
1795199746 11
1795199751 32
1795199756 32
1795199761 32
1795199766 32
1795199771 32
1795199776 32
1795199781 32
1795199786 32
1795199791 32
1795199796 32
1795199801 32
1795199806 32
1795199811 32
1795199816 32
1795199821 30
1795199826 30
1795199831 30
1795199836 30
1795199841 30
```
</details>

---

