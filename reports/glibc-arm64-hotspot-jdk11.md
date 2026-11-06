---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-06 07:08:25 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 10 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 27 |
| Sample Rate | 0.45/sec |
| Health Score | 28% |
| Threads | 7 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793966674 48
1793966679 48
1793966684 48
1793966689 48
1793966694 48
1793966699 48
1793966704 48
1793966709 48
1793966714 48
1793966719 48
1793966724 48
1793966729 48
1793966734 48
1793966739 48
1793966744 48
1793966749 48
1793966754 48
1793966759 48
1793966764 48
1793966769 48
```
</details>

---

