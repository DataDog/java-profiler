---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-23 05:49:38 EST

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
| CPU Cores (start) | 65 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 649 |
| Sample Rate | 10.82/sec |
| Health Score | 676% |
| Threads | 10 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (6 unique values: 61-75 cores)</summary>

```
1795430700 65
1795430705 63
1795430710 63
1795430715 63
1795430720 61
1795430725 61
1795430730 61
1795430735 61
1795430740 61
1795430745 61
1795430750 61
1795430755 61
1795430760 61
1795430765 61
1795430770 63
1795430775 63
1795430780 71
1795430785 71
1795430790 71
1795430795 71
```
</details>

---

