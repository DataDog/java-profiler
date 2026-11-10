---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-10 11:39:40 EST

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
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 8 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794328423 43
1794328428 43
1794328433 43
1794328438 43
1794328443 43
1794328448 48
1794328453 48
1794328458 48
1794328463 48
1794328468 48
1794328473 48
1794328478 48
1794328483 48
1794328488 48
1794328493 48
1794328498 48
1794328503 48
1794328508 48
1794328513 48
1794328518 48
```
</details>

---

