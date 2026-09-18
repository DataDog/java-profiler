---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 11:07:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 905 |
| Sample Rate | 15.08/sec |
| Health Score | 942% |
| Threads | 9 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (2 unique values: 58-64 cores)</summary>

```
1789743529 58
1789743535 58
1789743540 58
1789743545 58
1789743550 58
1789743555 58
1789743560 58
1789743565 58
1789743570 58
1789743575 58
1789743580 58
1789743585 58
1789743590 58
1789743595 64
1789743600 64
1789743605 64
1789743610 64
1789743615 64
1789743620 64
1789743625 64
```
</details>

---

