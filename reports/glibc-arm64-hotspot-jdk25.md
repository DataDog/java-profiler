---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-17 09:54:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
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
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 13 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (3 unique values: 40-48 cores)</summary>

```
1786974674 40
1786974679 40
1786974684 40
1786974689 40
1786974694 40
1786974699 40
1786974704 40
1786974709 40
1786974714 40
1786974719 40
1786974724 40
1786974729 40
1786974734 40
1786974739 40
1786974744 40
1786974749 40
1786974754 40
1786974759 40
1786974764 40
1786974769 40
```
</details>

---

