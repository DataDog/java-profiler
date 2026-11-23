---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-23 06:55:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 656 |
| Sample Rate | 10.93/sec |
| Health Score | 683% |
| Threads | 10 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (4 unique values: 42-71 cores)</summary>

```
1795434614 59
1795434619 59
1795434624 59
1795434629 59
1795434634 59
1795434639 59
1795434644 42
1795434649 42
1795434654 42
1795434659 70
1795434664 70
1795434669 70
1795434674 70
1795434679 70
1795434684 70
1795434689 71
1795434694 71
1795434699 71
1795434704 71
1795434709 71
```
</details>

---

