---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-07 19:05:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 403 |
| Sample Rate | 6.72/sec |
| Health Score | 420% |
| Threads | 10 |
| Allocations | 166 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 412 |
| Sample Rate | 6.87/sec |
| Health Score | 429% |
| Threads | 11 |
| Allocations | 191 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1778194840 64
1778194845 64
1778194850 64
1778194855 64
1778194860 64
1778194865 64
1778194870 64
1778194875 64
1778194880 64
1778194885 64
1778194890 64
1778194895 59
1778194900 59
1778194905 59
1778194910 59
1778194915 59
1778194920 59
1778194925 59
1778194930 59
1778194935 59
```
</details>

---

