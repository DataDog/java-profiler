---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 05:50:35 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 8 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 275 |
| Sample Rate | 4.58/sec |
| Health Score | 286% |
| Threads | 11 |
| Allocations | 125 |

<details>
<summary>CPU Timeline (4 unique values: 22-32 cores)</summary>

```
1795430690 22
1795430695 27
1795430700 27
1795430705 30
1795430710 30
1795430715 32
1795430720 32
1795430725 32
1795430730 32
1795430735 32
1795430740 32
1795430745 32
1795430750 32
1795430755 32
1795430760 32
1795430765 32
1795430770 32
1795430775 27
1795430780 27
1795430785 27
```
</details>

---

