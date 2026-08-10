---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-10 01:04:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 251 |
| Sample Rate | 4.18/sec |
| Health Score | 261% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 6 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 29-32 cores)</summary>

```
1786337953 32
1786337958 32
1786337963 32
1786337968 32
1786337973 32
1786337978 29
1786337983 29
1786337988 29
1786337993 29
1786337998 29
1786338003 29
1786338008 29
1786338013 29
1786338018 29
1786338023 29
1786338028 29
1786338033 29
1786338038 29
1786338043 29
1786338048 29
```
</details>

---

