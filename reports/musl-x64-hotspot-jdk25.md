---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-30 10:12:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 591 |
| Sample Rate | 9.85/sec |
| Health Score | 616% |
| Threads | 9 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 579 |
| Sample Rate | 9.65/sec |
| Health Score | 603% |
| Threads | 11 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (5 unique values: 70-88 cores)</summary>

```
1777558055 70
1777558060 70
1777558065 70
1777558070 70
1777558075 75
1777558080 75
1777558085 75
1777558090 75
1777558095 75
1777558100 75
1777558105 79
1777558110 79
1777558115 79
1777558120 83
1777558125 83
1777558130 88
1777558135 88
1777558140 88
1777558145 88
1777558150 88
```
</details>

---

