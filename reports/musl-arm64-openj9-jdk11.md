---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 17:21:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 391 |
| Sample Rate | 6.52/sec |
| Health Score | 407% |
| Threads | 11 |
| Allocations | 195 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 968 |
| Sample Rate | 16.13/sec |
| Health Score | 1008% |
| Threads | 9 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1794608211 36
1794608216 36
1794608221 36
1794608226 36
1794608231 36
1794608236 36
1794608241 36
1794608246 36
1794608251 36
1794608256 36
1794608261 36
1794608266 36
1794608271 36
1794608276 36
1794608281 36
1794608286 36
1794608291 36
1794608296 36
1794608301 36
1794608306 48
```
</details>

---

