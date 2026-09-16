---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-16 12:13:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 651 |
| Sample Rate | 10.85/sec |
| Health Score | 678% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 14 |
| Allocations | 75 |

<details>
<summary>CPU Timeline (2 unique values: 40-48 cores)</summary>

```
1789574817 40
1789574822 40
1789574827 40
1789574832 40
1789574837 40
1789574842 40
1789574847 40
1789574852 40
1789574857 40
1789574862 40
1789574872 40
1789574879 40
1789574888 40
1789574893 40
1789574905 40
1789574915 40
1789574920 40
1789574926 40
1789574931 40
1789574937 40
```
</details>

---

