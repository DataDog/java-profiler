---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-18 11:05:34 EDT

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 656 |
| Sample Rate | 10.93/sec |
| Health Score | 683% |
| Threads | 9 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 722 |
| Sample Rate | 12.03/sec |
| Health Score | 752% |
| Threads | 10 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (5 unique values: 72-96 cores)</summary>

```
1789743472 72
1789743477 96
1789743482 96
1789743487 96
1789743492 96
1789743497 96
1789743502 96
1789743507 96
1789743512 96
1789743517 94
1789743522 94
1789743527 94
1789743532 94
1789743537 94
1789743542 94
1789743547 94
1789743552 94
1789743557 78
1789743562 78
1789743567 78
```
</details>

---

