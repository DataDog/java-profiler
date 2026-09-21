---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-21 07:21:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 11 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (2 unique values: 22-27 cores)</summary>

```
1789989444 27
1789989449 27
1789989454 27
1789989459 22
1789989464 22
1789989469 22
1789989474 22
1789989479 22
1789989484 22
1789989489 22
1789989494 22
1789989499 22
1789989504 22
1789989509 27
1789989514 27
1789989519 27
1789989524 27
1789989529 27
1789989534 27
1789989539 27
```
</details>

---

