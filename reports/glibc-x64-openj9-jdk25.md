---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-21 17:43:36 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 378 |
| Sample Rate | 6.30/sec |
| Health Score | 394% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 11 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (2 unique values: 40-60 cores)</summary>

```
1790026715 40
1790026720 40
1790026725 40
1790026730 60
1790026735 60
1790026740 60
1790026745 60
1790026750 60
1790026755 60
1790026760 60
1790026765 60
1790026770 60
1790026775 60
1790026780 60
1790026785 60
1790026790 60
1790026795 60
1790026800 60
1790026805 60
1790026810 60
```
</details>

---

