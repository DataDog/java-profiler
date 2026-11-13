---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-13 13:36:36 EST

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
| CPU Cores (start) | 9 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 637 |
| Sample Rate | 10.62/sec |
| Health Score | 664% |
| Threads | 9 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (2 unique values: 9-11 cores)</summary>

```
1794594706 9
1794594711 9
1794594716 9
1794594721 9
1794594726 9
1794594731 9
1794594736 9
1794594741 9
1794594746 9
1794594751 9
1794594756 9
1794594761 9
1794594766 9
1794594771 9
1794594776 9
1794594781 9
1794594786 9
1794594791 9
1794594796 9
1794594801 9
```
</details>

---

