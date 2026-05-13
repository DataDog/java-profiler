---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-13 11:08:23 EDT

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 706 |
| Sample Rate | 11.77/sec |
| Health Score | 736% |
| Threads | 9 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (3 unique values: 78-96 cores)</summary>

```
1778684533 78
1778684538 78
1778684543 78
1778684548 78
1778684553 78
1778684558 87
1778684563 87
1778684568 87
1778684573 96
1778684578 96
1778684583 96
1778684588 96
1778684593 96
1778684598 96
1778684603 96
1778684608 96
1778684613 96
1778684619 96
1778684624 96
1778684629 96
```
</details>

---

