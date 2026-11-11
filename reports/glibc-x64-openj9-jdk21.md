---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-11 09:26:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
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
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 621 |
| Sample Rate | 10.35/sec |
| Health Score | 647% |
| Threads | 11 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (4 unique values: 72-92 cores)</summary>

```
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
1794407059 73
1794407064 73
1794407069 73
1794407074 73
```
</details>

---

