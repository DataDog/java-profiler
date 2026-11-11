---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 09:26:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 464 |
| Sample Rate | 7.73/sec |
| Health Score | 483% |
| Threads | 9 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 11 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (3 unique values: 75-79 cores)</summary>

```
1794406953 77
1794406958 77
1794406963 77
1794406968 75
1794406973 75
1794406978 75
1794406983 77
1794406988 77
1794406993 77
1794406998 77
1794407003 77
1794407008 77
1794407013 77
1794407018 77
1794407023 77
1794407028 77
1794407033 79
1794407038 79
1794407043 75
1794407048 75
```
</details>

---

