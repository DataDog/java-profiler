---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-17 13:54:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 271 |
| Sample Rate | 4.52/sec |
| Health Score | 282% |
| Threads | 12 |
| Allocations | 148 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 297 |
| Sample Rate | 4.95/sec |
| Health Score | 309% |
| Threads | 13 |
| Allocations | 101 |

<details>
<summary>CPU Timeline (2 unique values: 28-48 cores)</summary>

```
1789667257 48
1789667262 48
1789667267 48
1789667272 28
1789667277 28
1789667282 28
1789667287 28
1789667292 28
1789667297 28
1789667302 28
1789667307 28
1789667312 28
1789667317 28
1789667322 28
1789667327 28
1789667332 28
1789667338 28
1789667343 28
1789667348 28
1789667353 28
```
</details>

---

