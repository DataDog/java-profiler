---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-14 10:14:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 11 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (2 unique values: 63-64 cores)</summary>

```
1786716550 64
1786716555 64
1786716560 64
1786716565 64
1786716570 64
1786716575 64
1786716580 64
1786716585 64
1786716590 64
1786716595 64
1786716600 64
1786716605 64
1786716610 64
1786716615 64
1786716620 64
1786716625 64
1786716630 64
1786716635 64
1786716640 64
1786716645 64
```
</details>

---

