---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-18 11:09:00 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 9 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 13 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (2 unique values: 45-48 cores)</summary>

```
1789743403 45
1789743408 45
1789743413 45
1789743418 45
1789743423 45
1789743428 45
1789743433 45
1789743438 45
1789743443 45
1789743448 45
1789743453 45
1789743458 45
1789743463 45
1789743468 45
1789743473 45
1789743478 45
1789743483 45
1789743488 45
1789743493 48
1789743498 48
```
</details>

---

