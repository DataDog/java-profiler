---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 10:36:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 9 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 11 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (2 unique values: 44-64 cores)</summary>

```
1795620749 64
1795620754 64
1795620759 64
1795620764 64
1795620769 64
1795620774 64
1795620779 64
1795620784 64
1795620789 64
1795620794 44
1795620799 44
1795620804 44
1795620809 44
1795620815 44
1795620820 44
1795620825 44
1795620830 44
1795620835 44
1795620840 44
1795620845 44
```
</details>

---

