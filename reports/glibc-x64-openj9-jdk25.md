---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-01-29 09:48:26 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 563 |
| Sample Rate | 18.77/sec |
| Health Score | 1173% |
| Threads | 10 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 792 |
| Sample Rate | 26.40/sec |
| Health Score | 1650% |
| Threads | 12 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (3 unique values: 44-50 cores)</summary>

```
1769697768 50
1769697773 50
1769697778 50
1769697783 50
1769697788 50
1769697793 50
1769697798 50
1769697803 50
1769697808 50
1769697813 45
1769697818 45
1769697823 45
1769697828 44
1769697833 44
1769697838 44
1769697843 44
1769697848 44
1769697853 44
1769697858 44
1769697863 44
```
</details>

---

