---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-26 11:54:36 EST

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 10 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 8 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (2 unique values: 35-68 cores)</summary>

```
1795711826 68
1795711831 68
1795711836 68
1795711841 68
1795711846 68
1795711851 68
1795711856 68
1795711861 68
1795711866 68
1795711871 68
1795711876 35
1795711881 35
1795711886 35
1795711891 35
1795711896 35
1795711901 35
1795711906 35
1795711911 35
1795711916 35
1795711921 35
```
</details>

---

