---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-11 11:23:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 439 |
| Sample Rate | 7.32/sec |
| Health Score | 458% |
| Threads | 9 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 744 |
| Sample Rate | 12.40/sec |
| Health Score | 775% |
| Threads | 11 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (5 unique values: 43-48 cores)</summary>

```
1778512701 45
1778512706 45
1778512711 45
1778512716 43
1778512721 43
1778512726 43
1778512731 44
1778512736 44
1778512741 44
1778512746 44
1778512751 44
1778512756 44
1778512761 48
1778512766 48
1778512771 48
1778512776 48
1778512781 48
1778512786 46
1778512791 46
1778512796 46
```
</details>

---

