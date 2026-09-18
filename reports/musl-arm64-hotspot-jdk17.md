---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-18 04:31:59 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 84 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 13 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789719995 48
1789720000 48
1789720005 48
1789720010 48
1789720015 48
1789720020 48
1789720025 48
1789720030 48
1789720035 48
1789720040 48
1789720045 48
1789720050 48
1789720055 48
1789720060 48
1789720065 48
1789720070 48
1789720075 43
1789720080 43
1789720085 43
1789720090 43
```
</details>

---

