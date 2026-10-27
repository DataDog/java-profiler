---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-27 14:35:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
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
| CPU Samples | 341 |
| Sample Rate | 5.68/sec |
| Health Score | 355% |
| Threads | 11 |
| Allocations | 158 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793125819 48
1793125824 48
1793125829 48
1793125834 43
1793125839 43
1793125844 43
1793125849 43
1793125854 43
1793125859 43
1793125864 43
1793125869 43
1793125874 43
1793125879 43
1793125884 43
1793125889 43
1793125894 43
1793125899 43
1793125904 43
1793125909 43
1793125914 43
```
</details>

---

