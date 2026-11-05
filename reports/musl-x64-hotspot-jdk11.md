---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-05 11:16:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 10 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 868 |
| Sample Rate | 14.47/sec |
| Health Score | 904% |
| Threads | 11 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (2 unique values: 71-73 cores)</summary>

```
1793895006 73
1793895011 73
1793895016 73
1793895021 73
1793895026 73
1793895031 71
1793895036 71
1793895041 71
1793895046 71
1793895051 71
1793895056 71
1793895061 71
1793895066 71
1793895071 71
1793895076 71
1793895081 71
1793895086 71
1793895091 71
1793895096 71
1793895102 71
```
</details>

---

