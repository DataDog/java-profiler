---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-06 15:13:43 EST

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 761 |
| Sample Rate | 12.68/sec |
| Health Score | 792% |
| Threads | 11 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (2 unique values: 72-74 cores)</summary>

```
1793995825 74
1793995830 74
1793995835 74
1793995840 74
1793995845 74
1793995850 74
1793995855 74
1793995860 72
1793995865 72
1793995870 72
1793995875 72
1793995880 72
1793995885 72
1793995890 72
1793995895 72
1793995900 72
1793995905 72
1793995910 72
1793995915 72
1793995920 72
```
</details>

---

