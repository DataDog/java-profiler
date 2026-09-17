---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-17 15:36:17 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 8 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 10 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789673441 48
1789673446 48
1789673451 48
1789673456 48
1789673461 48
1789673466 48
1789673471 48
1789673476 48
1789673481 48
1789673486 48
1789673491 48
1789673496 48
1789673501 48
1789673506 48
1789673511 43
1789673516 43
1789673521 43
1789673526 43
1789673531 43
1789673536 43
```
</details>

---

