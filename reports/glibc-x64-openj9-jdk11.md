---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 13:27:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 8 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1043 |
| Sample Rate | 17.38/sec |
| Health Score | 1086% |
| Threads | 10 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (2 unique values: 76-94 cores)</summary>

```
1795112650 94
1795112655 94
1795112660 94
1795112665 94
1795112670 94
1795112675 94
1795112680 76
1795112685 76
1795112690 76
1795112695 76
1795112700 76
1795112705 76
1795112710 76
1795112715 76
1795112720 76
1795112725 76
1795112730 76
1795112735 76
1795112740 76
1795112745 76
```
</details>

---

