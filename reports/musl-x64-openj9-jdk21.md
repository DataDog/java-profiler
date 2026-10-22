---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-22 18:25:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 653 |
| Sample Rate | 10.88/sec |
| Health Score | 680% |
| Threads | 10 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (2 unique values: 23-25 cores)</summary>

```
1792707656 25
1792707661 25
1792707666 25
1792707671 25
1792707676 25
1792707681 25
1792707686 25
1792707691 25
1792707696 25
1792707701 25
1792707706 23
1792707711 23
1792707716 23
1792707721 23
1792707726 23
1792707731 23
1792707736 23
1792707741 23
1792707746 23
1792707751 23
```
</details>

---

