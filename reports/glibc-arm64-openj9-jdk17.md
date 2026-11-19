---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-19 12:10:53 EST

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 7 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (3 unique values: 30-42 cores)</summary>

```
1795107985 39
1795107990 39
1795107995 39
1795108000 39
1795108005 39
1795108010 39
1795108015 39
1795108020 39
1795108025 39
1795108030 39
1795108035 39
1795108040 39
1795108045 39
1795108050 42
1795108055 42
1795108060 42
1795108065 42
1795108070 42
1795108075 42
1795108080 42
```
</details>

---

