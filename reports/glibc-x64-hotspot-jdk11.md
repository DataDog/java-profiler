---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 06:56:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 8 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 865 |
| Sample Rate | 14.42/sec |
| Health Score | 901% |
| Threads | 9 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (2 unique values: 67-69 cores)</summary>

```
1795434729 67
1795434734 67
1795434739 67
1795434744 67
1795434749 67
1795434754 67
1795434759 67
1795434764 67
1795434769 67
1795434774 69
1795434779 69
1795434784 69
1795434789 69
1795434794 69
1795434799 69
1795434804 69
1795434809 69
1795434814 69
1795434819 69
1795434824 69
```
</details>

---

