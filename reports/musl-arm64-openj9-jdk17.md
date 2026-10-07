---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-07 10:47:24 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 12 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (5 unique values: 42-48 cores)</summary>

```
1791383986 43
1791383991 43
1791383996 43
1791384001 43
1791384006 42
1791384011 42
1791384016 42
1791384021 42
1791384026 42
1791384031 42
1791384036 47
1791384041 47
1791384046 48
1791384051 48
1791384056 46
1791384061 46
1791384066 46
1791384071 46
1791384076 43
1791384081 43
```
</details>

---

