---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-18 13:40:51 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 13 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 8 |
| Allocations | 85 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 11 |
| Allocations | 80 |

<details>
<summary>CPU Timeline (3 unique values: 13-44 cores)</summary>

```
1787074549 44
1787074554 44
1787074559 14
1787074564 14
1787074569 14
1787074574 14
1787074579 14
1787074584 14
1787074589 14
1787074594 14
1787074599 14
1787074604 14
1787074609 14
1787074614 14
1787074619 14
1787074624 14
1787074629 14
1787074634 14
1787074639 14
1787074644 14
```
</details>

---

