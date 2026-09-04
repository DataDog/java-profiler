---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-04 05:50:49 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 384 |
| Sample Rate | 6.40/sec |
| Health Score | 400% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 32-48 cores)</summary>

```
1788515208 32
1788515213 32
1788515218 32
1788515223 32
1788515228 32
1788515233 32
1788515238 32
1788515243 32
1788515248 32
1788515253 32
1788515258 32
1788515263 32
1788515268 32
1788515273 32
1788515278 44
1788515283 44
1788515288 44
1788515293 44
1788515298 44
1788515303 44
```
</details>

---

