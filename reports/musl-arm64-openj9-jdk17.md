---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-30 12:20:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 346 |
| Sample Rate | 5.77/sec |
| Health Score | 361% |
| Threads | 15 |
| Allocations | 135 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1790785019 48
1790785024 48
1790785029 48
1790785034 48
1790785039 48
1790785044 48
1790785049 48
1790785054 48
1790785059 48
1790785064 48
1790785069 48
1790785074 48
1790785079 48
1790785084 48
1790785089 48
1790785094 48
1790785099 48
1790785104 48
1790785109 48
1790785114 48
```
</details>

---

