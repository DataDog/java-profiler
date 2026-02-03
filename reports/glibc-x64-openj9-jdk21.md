---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-03 09:47:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 616 |
| Sample Rate | 10.27/sec |
| Health Score | 642% |
| Threads | 10 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 925 |
| Sample Rate | 15.42/sec |
| Health Score | 964% |
| Threads | 13 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (2 unique values: 76-78 cores)</summary>

```
1770129701 76
1770129706 76
1770129711 76
1770129716 76
1770129721 76
1770129726 76
1770129731 76
1770129736 76
1770129741 76
1770129746 76
1770129751 78
1770129756 78
1770129761 78
1770129766 78
1770129771 78
1770129776 78
1770129781 78
1770129786 78
1770129791 78
1770129796 78
```
</details>

---

