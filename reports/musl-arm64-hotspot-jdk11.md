---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-23 11:34:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 11 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 13 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790177364 50
1790177369 50
1790177374 50
1790177379 50
1790177385 50
1790177390 50
1790177395 50
1790177400 50
1790177405 50
1790177410 50
1790177415 50
1790177420 50
1790177425 50
1790177430 50
1790177435 50
1790177440 50
1790177445 50
1790177450 50
1790177455 50
1790177460 50
```
</details>

---

