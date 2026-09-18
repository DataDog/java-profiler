---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 04:30:59 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 738 |
| Sample Rate | 12.30/sec |
| Health Score | 769% |
| Threads | 9 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (3 unique values: 49-96 cores)</summary>

```
1789719942 49
1789719947 49
1789719952 49
1789719957 49
1789719962 49
1789719967 49
1789719972 49
1789719977 49
1789719982 49
1789719987 49
1789719992 49
1789719997 49
1789720002 49
1789720007 49
1789720012 96
1789720017 96
1789720022 61
1789720027 61
1789720032 61
1789720037 61
```
</details>

---

