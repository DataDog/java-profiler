---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-12 04:02:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (3 unique values: 54-64 cores)</summary>

```
1778572558 54
1778572563 54
1778572568 54
1778572573 54
1778572578 54
1778572583 59
1778572588 59
1778572593 59
1778572598 59
1778572603 59
1778572608 59
1778572613 59
1778572618 59
1778572623 64
1778572628 64
1778572633 64
1778572638 64
1778572643 64
1778572648 64
1778572653 64
```
</details>

---

