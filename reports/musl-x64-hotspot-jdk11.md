---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-19 05:04:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 8 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 856 |
| Sample Rate | 14.27/sec |
| Health Score | 892% |
| Threads | 10 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (3 unique values: 27-32 cores)</summary>

```
1792400090 30
1792400095 30
1792400100 30
1792400105 30
1792400110 30
1792400115 30
1792400120 30
1792400125 30
1792400130 30
1792400135 30
1792400140 30
1792400145 30
1792400150 32
1792400155 32
1792400160 27
1792400165 27
1792400170 27
1792400175 27
1792400180 27
1792400185 27
```
</details>

---

