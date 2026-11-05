---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-05 11:16:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 435 |
| Sample Rate | 7.25/sec |
| Health Score | 453% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 31-31 cores)</summary>

```
1793895026 31
1793895031 31
1793895036 31
1793895041 31
1793895046 31
1793895051 31
1793895056 31
1793895061 31
1793895066 31
1793895071 31
1793895076 31
1793895081 31
1793895086 31
1793895091 31
1793895096 31
1793895101 31
1793895106 31
1793895111 31
1793895116 31
1793895121 31
```
</details>

---

