---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 11:06:40 EDT

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 962 |
| Sample Rate | 16.03/sec |
| Health Score | 1002% |
| Threads | 9 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (5 unique values: 72-94 cores)</summary>

```
1789743504 94
1789743509 94
1789743514 94
1789743519 92
1789743524 92
1789743529 72
1789743534 72
1789743539 72
1789743544 72
1789743549 74
1789743554 74
1789743559 74
1789743564 74
1789743569 74
1789743574 74
1789743579 74
1789743584 74
1789743589 74
1789743594 74
1789743599 74
```
</details>

---

