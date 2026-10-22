---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-22 18:25:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 687 |
| Sample Rate | 11.45/sec |
| Health Score | 716% |
| Threads | 10 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (4 unique values: 76-91 cores)</summary>

```
1792707656 81
1792707661 76
1792707666 76
1792707671 79
1792707676 79
1792707681 79
1792707686 79
1792707691 79
1792707696 79
1792707701 79
1792707706 79
1792707711 79
1792707716 79
1792707721 81
1792707726 81
1792707731 81
1792707736 81
1792707741 81
1792707746 91
1792707751 91
```
</details>

---

