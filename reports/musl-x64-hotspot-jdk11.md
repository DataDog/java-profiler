---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 10:54:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 732 |
| Sample Rate | 12.20/sec |
| Health Score | 762% |
| Threads | 9 |
| Allocations | 552 |

<details>
<summary>CPU Timeline (2 unique values: 54-73 cores)</summary>

```
1794584948 73
1794584953 73
1794584958 73
1794584963 73
1794584968 73
1794584973 73
1794584978 73
1794584983 73
1794584988 73
1794584993 73
1794584998 73
1794585003 73
1794585008 73
1794585013 73
1794585018 73
1794585023 54
1794585028 54
1794585033 54
1794585038 54
1794585043 54
```
</details>

---

