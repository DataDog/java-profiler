---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 11:09:00 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 8 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 9 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (2 unique values: 45-48 cores)</summary>

```
1789743402 45
1789743407 45
1789743412 45
1789743417 45
1789743422 45
1789743427 45
1789743432 45
1789743437 45
1789743442 45
1789743447 45
1789743452 45
1789743457 45
1789743462 45
1789743467 45
1789743472 45
1789743477 45
1789743483 45
1789743488 45
1789743493 48
1789743498 48
```
</details>

---

