---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-21 07:21:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 10 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (4 unique values: 65-88 cores)</summary>

```
1789989424 76
1789989429 76
1789989434 78
1789989439 78
1789989444 78
1789989449 78
1789989454 78
1789989459 78
1789989464 78
1789989469 78
1789989474 78
1789989479 78
1789989484 88
1789989489 88
1789989494 88
1789989499 88
1789989504 88
1789989509 88
1789989514 88
1789989519 88
```
</details>

---

