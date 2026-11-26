---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-26 08:19:29 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 8 |
| Allocations | 40 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 79 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795698931 64
1795698936 64
1795698941 64
1795698946 64
1795698951 64
1795698956 64
1795698961 64
1795698966 64
1795698971 64
1795698976 64
1795698981 64
1795698986 64
1795698991 64
1795698996 64
1795699001 64
1795699006 64
1795699011 64
1795699016 64
1795699021 64
1795699026 64
```
</details>

---

