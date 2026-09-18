---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 11:11:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 10 |
| Allocations | 85 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 12 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789743509 43
1789743514 43
1789743519 43
1789743524 43
1789743529 43
1789743534 48
1789743539 48
1789743544 48
1789743549 48
1789743554 48
1789743559 48
1789743564 48
1789743569 48
1789743574 48
1789743579 48
1789743584 48
1789743589 48
1789743594 48
1789743599 48
1789743604 48
```
</details>

---

