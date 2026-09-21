---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-21 07:21:18 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 8 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 12 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (3 unique values: 44-64 cores)</summary>

```
1789989424 49
1789989429 49
1789989434 49
1789989439 49
1789989444 49
1789989449 49
1789989454 49
1789989459 64
1789989464 64
1789989469 64
1789989474 64
1789989479 64
1789989484 64
1789989489 64
1789989494 44
1789989499 44
1789989504 44
1789989509 44
1789989514 44
1789989519 44
```
</details>

---

