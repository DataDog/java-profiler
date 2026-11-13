---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 10:16:37 EST

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
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 11 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 229 |
| Sample Rate | 3.82/sec |
| Health Score | 239% |
| Threads | 11 |
| Allocations | 131 |

<details>
<summary>CPU Timeline (2 unique values: 47-48 cores)</summary>

```
1794582670 47
1794582675 47
1794582680 47
1794582685 47
1794582690 47
1794582695 47
1794582700 47
1794582705 47
1794582710 47
1794582715 47
1794582720 47
1794582725 48
1794582730 48
1794582735 48
1794582740 48
1794582745 48
1794582750 48
1794582755 48
1794582760 48
1794582765 48
```
</details>

---

