---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-27 07:00:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 10 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (4 unique values: 42-83 cores)</summary>

```
1793098456 83
1793098461 83
1793098466 83
1793098471 63
1793098476 63
1793098481 63
1793098486 63
1793098491 63
1793098496 63
1793098501 63
1793098506 63
1793098511 63
1793098516 63
1793098521 42
1793098526 42
1793098531 42
1793098536 42
1793098541 42
1793098546 42
1793098551 42
```
</details>

---

