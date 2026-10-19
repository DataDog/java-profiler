---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-18 21:26:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 17 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 8 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 8 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (2 unique values: 15-17 cores)</summary>

```
1792372807 17
1792372812 17
1792372817 17
1792372822 17
1792372827 17
1792372832 17
1792372837 15
1792372842 15
1792372847 15
1792372852 15
1792372857 15
1792372862 15
1792372867 15
1792372872 15
1792372877 17
1792372882 17
1792372887 17
1792372892 17
1792372897 17
1792372902 17
```
</details>

---

