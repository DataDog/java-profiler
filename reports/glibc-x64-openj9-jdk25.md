---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-07 16:34:36 EDT

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 405 |
| Sample Rate | 6.75/sec |
| Health Score | 422% |
| Threads | 9 |
| Allocations | 430 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 622 |
| Sample Rate | 10.37/sec |
| Health Score | 648% |
| Threads | 11 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (3 unique values: 66-76 cores)</summary>

```
1778185642 71
1778185647 71
1778185652 71
1778185657 71
1778185662 71
1778185667 71
1778185672 71
1778185677 76
1778185682 76
1778185687 76
1778185692 66
1778185697 66
1778185702 66
1778185707 66
1778185712 66
1778185717 66
1778185722 66
1778185727 66
1778185732 66
1778185737 66
```
</details>

---

