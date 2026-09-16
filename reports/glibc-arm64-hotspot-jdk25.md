---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-16 07:29:58 EDT

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 45 |
| Sample Rate | 0.75/sec |
| Health Score | 47% |
| Threads | 8 |
| Allocations | 46 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 8 |
| Allocations | 4 |

<details>
<summary>CPU Timeline (4 unique values: 27-33 cores)</summary>

```
1789557871 33
1789557876 33
1789557881 33
1789557886 32
1789557891 32
1789557896 32
1789557901 32
1789557906 32
1789557911 32
1789557916 32
1789557921 32
1789557926 32
1789557931 32
1789557936 32
1789557941 32
1789557946 27
1789557951 27
1789557956 27
1789557961 28
1789557966 28
```
</details>

---

