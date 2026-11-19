---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-19 11:53:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 11.30/sec |
| Health Score | 706% |
| Threads | 11 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795106974 50
1795106979 50
1795106984 50
1795106989 50
1795106994 50
1795106999 50
1795107004 50
1795107009 50
1795107014 50
1795107019 50
1795107024 50
1795107029 50
1795107034 50
1795107039 50
1795107044 50
1795107049 50
1795107054 50
1795107059 50
1795107064 50
1795107069 50
```
</details>

---

