---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-27 10:59:06 EST

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 124 |
| Sample Rate | 2.07/sec |
| Health Score | 129% |
| Threads | 11 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 7 |
| Allocations | 3 |

<details>
<summary>CPU Timeline (2 unique values: 56-58 cores)</summary>

```
1795794913 58
1795794918 58
1795794923 58
1795794928 58
1795794933 58
1795794938 58
1795794943 58
1795794948 58
1795794953 58
1795794958 58
1795794963 58
1795794968 58
1795794973 58
1795794978 58
1795794983 58
1795794988 58
1795794993 58
1795794998 58
1795795003 56
1795795009 56
```
</details>

---

