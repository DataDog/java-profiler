---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-23 04:42:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 12 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 867 |
| Sample Rate | 14.45/sec |
| Health Score | 903% |
| Threads | 11 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (3 unique values: 44-64 cores)</summary>

```
1795426738 44
1795426743 44
1795426748 44
1795426753 44
1795426758 44
1795426763 44
1795426768 44
1795426773 44
1795426778 44
1795426783 44
1795426788 44
1795426793 49
1795426798 49
1795426803 49
1795426809 49
1795426814 49
1795426819 49
1795426824 49
1795426829 49
1795426834 49
```
</details>

---

