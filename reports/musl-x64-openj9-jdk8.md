---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-13 10:15:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 19 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 297 |
| Sample Rate | 4.95/sec |
| Health Score | 309% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 250 |
| Sample Rate | 4.17/sec |
| Health Score | 261% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 19-24 cores)</summary>

```
1794582670 19
1794582675 19
1794582680 19
1794582685 19
1794582690 19
1794582695 19
1794582700 19
1794582705 19
1794582710 19
1794582715 19
1794582720 19
1794582725 19
1794582730 19
1794582735 19
1794582740 19
1794582745 19
1794582750 19
1794582755 19
1794582760 19
1794582765 21
```
</details>

---

