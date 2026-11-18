---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 09:10:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 571 |
| Sample Rate | 9.52/sec |
| Health Score | 595% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 736 |
| Sample Rate | 12.27/sec |
| Health Score | 767% |
| Threads | 11 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (4 unique values: 76-87 cores)</summary>

```
1795010714 76
1795010719 78
1795010724 78
1795010729 78
1795010734 78
1795010739 78
1795010744 78
1795010749 78
1795010754 78
1795010759 78
1795010764 78
1795010769 78
1795010774 78
1795010779 78
1795010784 78
1795010789 87
1795010794 87
1795010799 85
1795010804 85
1795010809 85
```
</details>

---

