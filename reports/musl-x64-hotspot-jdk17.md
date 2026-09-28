---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-28 00:58:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 645 |
| Sample Rate | 10.75/sec |
| Health Score | 672% |
| Threads | 10 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (3 unique values: 29-49 cores)</summary>

```
1790571203 29
1790571208 49
1790571213 49
1790571218 49
1790571223 49
1790571228 49
1790571233 49
1790571238 49
1790571243 49
1790571248 49
1790571253 49
1790571258 49
1790571263 49
1790571268 49
1790571273 49
1790571278 49
1790571283 34
1790571288 34
1790571293 34
1790571298 34
```
</details>

---

