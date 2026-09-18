---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-18 11:13:59 EDT

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (2 unique values: 25-35 cores)</summary>

```
1789743355 35
1789743360 35
1789743365 35
1789743370 35
1789743375 35
1789743380 35
1789743385 35
1789743390 35
1789743395 35
1789743400 35
1789743405 35
1789743410 35
1789743415 35
1789743420 25
1789743425 25
1789743430 25
1789743435 25
1789743440 25
1789743445 25
1789743450 25
```
</details>

---

