---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-27 06:17:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 11 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 11 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (3 unique values: 27-33 cores)</summary>

```
1795778029 27
1795778034 33
1795778039 33
1795778044 33
1795778049 33
1795778054 33
1795778059 33
1795778064 33
1795778069 33
1795778074 33
1795778079 33
1795778084 31
1795778089 31
1795778094 31
1795778099 31
1795778104 31
1795778109 31
1795778114 31
1795778119 31
1795778124 31
```
</details>

---

