---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-24 08:33:46 EDT

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 9 |
| Allocations | 415 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 821 |
| Sample Rate | 13.68/sec |
| Health Score | 855% |
| Threads | 10 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (5 unique values: 42-74 cores)</summary>

```
1777033632 56
1777033637 56
1777033642 60
1777033647 60
1777033652 60
1777033657 60
1777033662 60
1777033667 60
1777033672 62
1777033677 62
1777033682 42
1777033687 42
1777033692 42
1777033697 42
1777033702 42
1777033707 42
1777033712 42
1777033717 42
1777033723 42
1777033728 42
```
</details>

---

