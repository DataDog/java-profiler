---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 05:16:18 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 339 |
| Sample Rate | 5.65/sec |
| Health Score | 353% |
| Threads | 9 |
| Allocations | 332 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 12 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (3 unique values: 43-47 cores)</summary>

```
1794823695 47
1794823700 47
1794823705 46
1794823710 46
1794823715 46
1794823720 46
1794823725 47
1794823730 47
1794823735 46
1794823740 46
1794823745 43
1794823750 43
1794823755 43
1794823760 43
1794823765 43
1794823770 43
1794823775 43
1794823780 43
1794823785 43
1794823790 43
```
</details>

---

