---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-09 21:25:28 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 131 |
| Sample Rate | 2.18/sec |
| Health Score | 136% |
| Threads | 8 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 400 |
| Sample Rate | 6.67/sec |
| Health Score | 417% |
| Threads | 12 |
| Allocations | 157 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1786324719 64
1786324724 64
1786324729 64
1786324734 64
1786324739 64
1786324744 64
1786324749 64
1786324754 64
1786324759 64
1786324764 64
1786324769 64
1786324774 64
1786324779 64
1786324784 64
1786324789 64
1786324794 64
1786324799 64
1786324804 64
1786324809 64
1786324814 64
```
</details>

---

