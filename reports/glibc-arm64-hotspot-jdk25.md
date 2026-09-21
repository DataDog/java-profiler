---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-21 00:47:24 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 12 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789965844 48
1789965849 48
1789965854 48
1789965859 48
1789965864 48
1789965869 48
1789965874 48
1789965879 48
1789965884 48
1789965889 43
1789965894 43
1789965899 43
1789965904 43
1789965909 43
1789965914 43
1789965919 43
1789965924 43
1789965929 43
1789965934 43
1789965939 43
```
</details>

---

