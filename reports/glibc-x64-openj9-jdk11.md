---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 13:22:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 8 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 755 |
| Sample Rate | 12.58/sec |
| Health Score | 786% |
| Threads | 10 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (3 unique values: 70-74 cores)</summary>

```
1795025880 70
1795025885 70
1795025890 70
1795025895 70
1795025900 72
1795025905 72
1795025910 72
1795025915 72
1795025920 72
1795025925 72
1795025930 72
1795025935 72
1795025940 72
1795025945 72
1795025950 72
1795025955 72
1795025960 72
1795025965 74
1795025970 74
1795025975 72
```
</details>

---

