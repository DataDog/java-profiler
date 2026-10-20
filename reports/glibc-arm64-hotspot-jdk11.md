---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-20 17:52:25 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 11 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 22 |
| Sample Rate | 0.37/sec |
| Health Score | 23% |
| Threads | 6 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (2 unique values: 28-48 cores)</summary>

```
1792532764 28
1792532769 28
1792532774 28
1792532779 28
1792532784 28
1792532789 28
1792532794 28
1792532799 28
1792532804 28
1792532809 28
1792532814 28
1792532819 28
1792532824 28
1792532829 28
1792532834 28
1792532839 28
1792532844 28
1792532849 28
1792532854 28
1792532859 28
```
</details>

---

