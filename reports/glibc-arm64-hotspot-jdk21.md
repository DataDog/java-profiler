---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-24 12:21:54 EST

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
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 9 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (3 unique values: 43-64 cores)</summary>

```
1795540667 48
1795540672 48
1795540677 48
1795540682 48
1795540687 48
1795540692 48
1795540697 48
1795540702 64
1795540707 64
1795540712 64
1795540717 64
1795540722 64
1795540727 64
1795540732 64
1795540737 64
1795540742 64
1795540747 64
1795540752 64
1795540757 64
1795540762 64
```
</details>

---

