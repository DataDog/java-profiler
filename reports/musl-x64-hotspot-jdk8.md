---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-12 10:09:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 441 |
| Sample Rate | 7.35/sec |
| Health Score | 459% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 425 |
| Sample Rate | 7.08/sec |
| Health Score | 442% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 57-83 cores)</summary>

```
1794495882 83
1794495887 83
1794495892 83
1794495897 83
1794495902 83
1794495907 83
1794495912 83
1794495917 83
1794495922 83
1794495927 57
1794495932 57
1794495937 57
1794495942 57
1794495947 57
1794495952 57
1794495957 57
1794495962 57
1794495967 57
1794495972 57
1794495977 57
```
</details>

---

