---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-10 19:10:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 7 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 752 |
| Sample Rate | 12.53/sec |
| Health Score | 783% |
| Threads | 11 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794355567 48
1794355572 48
1794355577 48
1794355582 48
1794355587 48
1794355592 48
1794355597 48
1794355602 48
1794355607 48
1794355612 48
1794355617 43
1794355622 43
1794355627 43
1794355632 43
1794355637 43
1794355642 43
1794355647 43
1794355652 43
1794355657 43
1794355662 43
```
</details>

---

