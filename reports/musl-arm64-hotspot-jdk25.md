---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-30 00:57:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 14 |
| Allocations | 77 |

<details>
<summary>CPU Timeline (2 unique values: 23-28 cores)</summary>

```
1788065554 23
1788065559 23
1788065564 23
1788065569 23
1788065574 23
1788065579 23
1788065584 23
1788065589 23
1788065594 23
1788065599 23
1788065604 23
1788065609 23
1788065614 23
1788065619 23
1788065624 23
1788065629 23
1788065634 28
1788065639 28
1788065644 28
1788065649 28
```
</details>

---

