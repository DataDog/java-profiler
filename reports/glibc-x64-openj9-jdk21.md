---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-29 08:13:29 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 411 |
| Sample Rate | 6.85/sec |
| Health Score | 428% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 604 |
| Sample Rate | 10.07/sec |
| Health Score | 629% |
| Threads | 10 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (5 unique values: 48-57 cores)</summary>

```
1793275701 48
1793275706 48
1793275711 48
1793275716 48
1793275721 48
1793275726 48
1793275731 48
1793275736 48
1793275741 48
1793275746 48
1793275751 51
1793275756 51
1793275761 51
1793275766 51
1793275771 51
1793275776 51
1793275781 57
1793275786 57
1793275791 57
1793275796 55
```
</details>

---

