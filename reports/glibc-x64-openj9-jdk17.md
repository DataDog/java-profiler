---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-22 18:25:50 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 554 |
| Sample Rate | 9.23/sec |
| Health Score | 577% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 10 |
| Allocations | 433 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1792707706 48
1792707711 48
1792707716 48
1792707721 48
1792707726 48
1792707731 48
1792707736 48
1792707741 48
1792707746 48
1792707751 48
1792707756 48
1792707761 48
1792707766 48
1792707771 48
1792707776 48
1792707781 48
1792707786 48
1792707791 46
1792707796 46
1792707801 46
```
</details>

---

