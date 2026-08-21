---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-21 05:42:04 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 415 |
| Sample Rate | 6.92/sec |
| Health Score | 432% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 10 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1787305092 46
1787305097 46
1787305102 46
1787305107 46
1787305112 46
1787305117 46
1787305122 46
1787305127 46
1787305132 46
1787305137 46
1787305142 48
1787305147 48
1787305152 48
1787305157 48
1787305162 48
1787305167 48
1787305172 48
1787305177 48
1787305182 48
1787305187 48
```
</details>

---

