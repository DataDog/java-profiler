---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 16:23:58 EST

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 9 |
| Allocations | 331 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 11 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (3 unique values: 59-67 cores)</summary>

```
1794604752 67
1794604757 67
1794604762 65
1794604767 65
1794604772 65
1794604777 67
1794604782 67
1794604787 67
1794604792 67
1794604797 67
1794604802 67
1794604807 67
1794604812 67
1794604817 67
1794604822 67
1794604828 67
1794604833 67
1794604838 67
1794604843 67
1794604848 67
```
</details>

---

