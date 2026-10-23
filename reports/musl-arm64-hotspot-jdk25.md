---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-23 08:55:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 45 |
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
| Allocations | 46 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 11 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (5 unique values: 36-45 cores)</summary>

```
1792759860 41
1792759865 41
1792759870 41
1792759875 41
1792759880 41
1792759885 41
1792759890 41
1792759895 36
1792759900 36
1792759905 36
1792759910 36
1792759915 37
1792759920 37
1792759925 39
1792759930 39
1792759935 39
1792759940 39
1792759945 39
1792759950 39
1792759956 39
```
</details>

---

