---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-18 11:06:40 EDT

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
| CPU Cores (start) | 15 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 8 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 13 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (2 unique values: 15-32 cores)</summary>

```
1789743497 15
1789743502 15
1789743507 15
1789743512 15
1789743517 15
1789743522 15
1789743527 15
1789743532 15
1789743537 15
1789743542 15
1789743547 15
1789743552 15
1789743557 15
1789743562 15
1789743567 32
1789743572 32
1789743577 15
1789743582 15
1789743587 15
1789743592 15
```
</details>

---

