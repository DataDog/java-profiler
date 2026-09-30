---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-30 07:14:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 9 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 706 |
| Sample Rate | 11.77/sec |
| Health Score | 736% |
| Threads | 9 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (5 unique values: 32-37 cores)</summary>

```
1790766558 35
1790766563 35
1790766568 35
1790766573 35
1790766578 35
1790766583 35
1790766588 35
1790766593 35
1790766598 34
1790766603 34
1790766608 32
1790766613 32
1790766618 32
1790766623 32
1790766628 37
1790766633 37
1790766638 32
1790766643 32
1790766648 32
1790766653 32
```
</details>

---

