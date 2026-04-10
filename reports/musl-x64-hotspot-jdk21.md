---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-10 19:29:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 659 |
| Sample Rate | 10.98/sec |
| Health Score | 686% |
| Threads | 10 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (2 unique values: 64-68 cores)</summary>

```
1775863629 68
1775863634 68
1775863639 68
1775863644 68
1775863649 68
1775863654 68
1775863659 68
1775863664 68
1775863669 68
1775863674 68
1775863679 68
1775863684 68
1775863689 68
1775863694 68
1775863699 68
1775863704 68
1775863709 64
1775863714 64
1775863719 64
1775863724 64
```
</details>

---

