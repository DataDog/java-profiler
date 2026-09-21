---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-21 04:45:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 10.47/sec |
| Health Score | 654% |
| Threads | 9 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (3 unique values: 45-96 cores)</summary>

```
1789979986 45
1789979991 45
1789979996 45
1789980001 45
1789980006 45
1789980011 45
1789980016 45
1789980021 45
1789980026 45
1789980031 45
1789980036 45
1789980041 71
1789980046 71
1789980051 71
1789980056 71
1789980061 96
1789980066 96
1789980071 96
1789980076 96
1789980081 96
```
</details>

---

