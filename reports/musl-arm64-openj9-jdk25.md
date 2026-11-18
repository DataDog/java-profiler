---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 13:22:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 132 |
| Sample Rate | 2.20/sec |
| Health Score | 138% |
| Threads | 9 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 759 |
| Sample Rate | 12.65/sec |
| Health Score | 791% |
| Threads | 10 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1795025860 29
1795025865 29
1795025870 29
1795025875 29
1795025880 34
1795025885 34
1795025890 34
1795025895 34
1795025900 29
1795025905 29
1795025910 29
1795025915 29
1795025920 29
1795025925 29
1795025930 29
1795025935 29
1795025940 29
1795025945 29
1795025950 29
1795025955 29
```
</details>

---

