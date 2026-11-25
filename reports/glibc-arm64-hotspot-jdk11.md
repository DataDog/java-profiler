---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 10:49:48 EST

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
| CPU Cores (start) | 17 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 11 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (4 unique values: 15-18 cores)</summary>

```
1795621547 17
1795621552 15
1795621557 15
1795621562 15
1795621567 15
1795621572 16
1795621577 16
1795621582 16
1795621587 16
1795621592 16
1795621597 16
1795621602 16
1795621607 16
1795621612 16
1795621617 16
1795621622 18
1795621627 18
1795621632 18
1795621637 16
1795621642 16
```
</details>

---

