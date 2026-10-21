---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-21 08:20:54 EDT

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 297 |
| Sample Rate | 4.95/sec |
| Health Score | 309% |
| Threads | 12 |
| Allocations | 143 |

<details>
<summary>CPU Timeline (3 unique values: 35-41 cores)</summary>

```
1792584850 35
1792584855 35
1792584860 37
1792584865 37
1792584870 37
1792584875 37
1792584880 37
1792584885 37
1792584890 37
1792584895 41
1792584900 41
1792584905 41
1792584910 41
1792584915 41
1792584920 41
1792584925 41
1792584930 41
1792584935 41
1792584940 41
1792584945 41
```
</details>

---

