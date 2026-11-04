---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-04 15:01:26 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 321 |
| Sample Rate | 5.35/sec |
| Health Score | 334% |
| Threads | 13 |
| Allocations | 116 |

<details>
<summary>CPU Timeline (2 unique values: 30-51 cores)</summary>

```
1793822229 51
1793822234 51
1793822239 51
1793822244 51
1793822249 51
1793822254 51
1793822259 51
1793822264 51
1793822269 51
1793822274 51
1793822279 51
1793822284 51
1793822289 51
1793822294 51
1793822299 51
1793822304 30
1793822309 30
1793822314 30
1793822319 30
1793822324 30
```
</details>

---

