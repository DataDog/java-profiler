---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-30 12:20:49 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 920 |
| Sample Rate | 15.33/sec |
| Health Score | 958% |
| Threads | 11 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (2 unique values: 69-81 cores)</summary>

```
1790785024 81
1790785029 81
1790785034 81
1790785039 81
1790785044 81
1790785049 81
1790785054 81
1790785059 81
1790785064 81
1790785069 81
1790785074 81
1790785079 81
1790785084 81
1790785089 81
1790785094 81
1790785099 81
1790785104 81
1790785109 81
1790785114 81
1790785119 81
```
</details>

---

