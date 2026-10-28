---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-28 07:43:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
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
| Threads | 10 |
| Allocations | 44 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 12 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793187446 43
1793187451 43
1793187456 43
1793187461 43
1793187466 43
1793187471 43
1793187476 43
1793187481 43
1793187486 43
1793187491 43
1793187496 43
1793187501 43
1793187506 43
1793187511 43
1793187516 43
1793187521 43
1793187526 43
1793187531 43
1793187536 48
1793187541 48
```
</details>

---

