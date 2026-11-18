---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 05:59:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 13 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (1 unique values: 15-15 cores)</summary>

```
1794999238 15
1794999243 15
1794999248 15
1794999253 15
1794999258 15
1794999263 15
1794999268 15
1794999273 15
1794999278 15
1794999283 15
1794999288 15
1794999293 15
1794999298 15
1794999303 15
1794999308 15
1794999313 15
1794999318 15
1794999323 15
1794999328 15
1794999333 15
```
</details>

---

