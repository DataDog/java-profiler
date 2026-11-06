---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-05 20:23:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 8 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 655 |
| Sample Rate | 10.92/sec |
| Health Score | 682% |
| Threads | 9 |
| Allocations | 560 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1793927856 40
1793927861 40
1793927866 40
1793927871 40
1793927876 40
1793927881 40
1793927886 40
1793927891 40
1793927896 40
1793927901 40
1793927906 40
1793927911 40
1793927916 40
1793927921 40
1793927926 40
1793927931 40
1793927936 40
1793927941 40
1793927946 40
1793927951 40
```
</details>

---

