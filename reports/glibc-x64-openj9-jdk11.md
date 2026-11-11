---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 09:26:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 664 |
| Sample Rate | 11.07/sec |
| Health Score | 692% |
| Threads | 9 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (4 unique values: 72-92 cores)</summary>

```
1794406963 72
1794406968 72
1794406973 72
1794406978 72
1794406983 72
1794406988 72
1794406993 72
1794406998 72
1794407003 72
1794407008 72
1794407013 72
1794407018 72
1794407023 72
1794407028 72
1794407033 72
1794407038 72
1794407043 75
1794407048 75
1794407053 75
1794407058 73
```
</details>

---

