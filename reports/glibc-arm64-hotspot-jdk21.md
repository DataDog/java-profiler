---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-30 13:48:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 8 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 11 |
| Allocations | 75 |

<details>
<summary>CPU Timeline (4 unique values: 42-48 cores)</summary>

```
1793382267 42
1793382272 42
1793382277 42
1793382282 42
1793382287 42
1793382292 42
1793382297 42
1793382302 42
1793382307 42
1793382312 42
1793382317 42
1793382322 42
1793382327 42
1793382332 44
1793382337 44
1793382342 44
1793382347 44
1793382352 44
1793382357 44
1793382362 44
```
</details>

---

