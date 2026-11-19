---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-19 11:53:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
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
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 11 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 11 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795106971 50
1795106976 50
1795106981 50
1795106986 50
1795106991 50
1795106996 50
1795107001 50
1795107006 50
1795107011 50
1795107016 50
1795107021 50
1795107026 50
1795107031 50
1795107036 50
1795107041 50
1795107046 50
1795107051 50
1795107056 50
1795107061 50
1795107066 50
```
</details>

---

