---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 07:41:12 EST

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 8 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 13 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (3 unique values: 39-48 cores)</summary>

```
1794487001 39
1794487006 39
1794487011 39
1794487016 39
1794487021 39
1794487026 39
1794487031 39
1794487036 39
1794487041 43
1794487046 43
1794487051 48
1794487056 48
1794487061 48
1794487066 48
1794487071 48
1794487076 48
1794487081 48
1794487086 48
1794487091 48
1794487096 48
```
</details>

---

