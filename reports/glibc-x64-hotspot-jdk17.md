---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-13 13:50:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 86 |
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
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 602 |
| Sample Rate | 10.03/sec |
| Health Score | 627% |
| Threads | 11 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (4 unique values: 82-88 cores)</summary>

```
1794595542 82
1794595547 82
1794595552 82
1794595557 88
1794595562 88
1794595567 88
1794595572 88
1794595577 88
1794595582 88
1794595587 88
1794595592 88
1794595597 88
1794595602 88
1794595607 84
1794595612 84
1794595617 84
1794595622 84
1794595627 84
1794595632 86
1794595637 86
```
</details>

---

