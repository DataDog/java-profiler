---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-20 07:04:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 13 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (2 unique values: 18-22 cores)</summary>

```
1795175968 18
1795175973 18
1795175978 22
1795175983 22
1795175988 22
1795175993 22
1795175998 22
1795176003 22
1795176008 22
1795176013 22
1795176018 22
1795176023 22
1795176028 22
1795176033 22
1795176038 22
1795176043 22
1795176048 22
1795176053 22
1795176058 22
1795176063 22
```
</details>

---

