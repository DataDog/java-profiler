---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ❌ FAIL

**Date:** 2026-11-19 06:06:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 361 |
| Sample Rate | 6.02/sec |
| Health Score | 376% |
| Threads | 12 |
| Allocations | 160 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 38-38 cores)</summary>

```
1795085973 38
1795085978 38
1795085983 38
1795085988 38
1795085993 38
1795085998 38
1795086003 38
1795086008 38
1795086014 38
1795086019 38
1795086024 38
1795086029 38
1795086034 38
1795086039 38
1795086044 38
1795086049 38
1795086054 38
1795086059 38
1795086064 38
1795086069 38
```
</details>

---

