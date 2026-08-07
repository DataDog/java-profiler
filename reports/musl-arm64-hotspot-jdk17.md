---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-07 10:30:56 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 402 |
| Sample Rate | 6.70/sec |
| Health Score | 419% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 10 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (2 unique values: 23-24 cores)</summary>

```
1786112753 24
1786112758 24
1786112763 24
1786112768 24
1786112773 24
1786112778 24
1786112783 24
1786112788 24
1786112793 24
1786112798 23
1786112804 23
1786112809 23
1786112814 23
1786112819 23
1786112824 23
1786112829 23
1786112834 23
1786112839 23
1786112844 23
1786112849 23
```
</details>

---

