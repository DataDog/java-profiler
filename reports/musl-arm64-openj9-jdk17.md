---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 07:21:47 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 7 |
| Allocations | 87 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 9 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (3 unique values: 28-48 cores)</summary>

```
1789730249 44
1789730254 44
1789730259 44
1789730264 48
1789730269 48
1789730274 28
1789730279 28
1789730284 28
1789730289 28
1789730294 28
1789730299 28
1789730304 28
1789730309 28
1789730314 28
1789730319 28
1789730324 28
1789730329 28
1789730334 28
1789730339 28
1789730344 28
```
</details>

---

