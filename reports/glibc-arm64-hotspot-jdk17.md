---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-17 17:31:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 8 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 12 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789680263 43
1789680268 43
1789680273 43
1789680278 43
1789680283 48
1789680288 48
1789680293 48
1789680298 48
1789680303 48
1789680308 48
1789680313 48
1789680318 48
1789680323 48
1789680328 48
1789680333 43
1789680338 43
1789680343 43
1789680348 43
1789680353 43
1789680358 43
```
</details>

---

