---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-15 03:56:29 EDT

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 464 |
| Sample Rate | 7.73/sec |
| Health Score | 483% |
| Threads | 9 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 10.30/sec |
| Health Score | 644% |
| Threads | 10 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (4 unique values: 39-52 cores)</summary>

```
1792050706 52
1792050711 52
1792050716 52
1792050721 52
1792050726 52
1792050731 52
1792050736 52
1792050741 52
1792050746 52
1792050751 43
1792050756 43
1792050761 41
1792050766 41
1792050771 39
1792050776 39
1792050781 39
1792050786 39
1792050791 39
1792050796 41
1792050801 41
```
</details>

---

