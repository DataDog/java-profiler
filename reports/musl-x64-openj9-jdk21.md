---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-27 06:17:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 709 |
| Sample Rate | 11.82/sec |
| Health Score | 739% |
| Threads | 11 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (2 unique values: 39-42 cores)</summary>

```
1795778001 39
1795778006 39
1795778011 39
1795778016 39
1795778021 39
1795778026 39
1795778031 39
1795778036 39
1795778041 39
1795778046 42
1795778051 42
1795778056 42
1795778061 42
1795778066 42
1795778071 42
1795778076 42
1795778081 42
1795778086 42
1795778091 42
1795778096 42
```
</details>

---

