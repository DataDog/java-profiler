---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-18 13:40:51 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 13 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 15 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787074599 48
1787074604 48
1787074609 48
1787074614 48
1787074619 48
1787074624 48
1787074629 48
1787074634 48
1787074639 48
1787074644 48
1787074649 48
1787074654 48
1787074659 48
1787074664 48
1787074669 48
1787074674 48
1787074679 43
1787074684 43
1787074689 43
1787074694 43
```
</details>

---

