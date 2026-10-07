---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-07 10:47:25 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (6 unique values: 38-48 cores)</summary>

```
1791383990 43
1791383995 43
1791384000 43
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
1791384086 43
```
</details>

---

