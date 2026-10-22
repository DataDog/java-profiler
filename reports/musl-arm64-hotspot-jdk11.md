---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-22 08:46:39 EDT

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 11 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 13 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (3 unique values: 35-54 cores)</summary>

```
1792672953 35
1792672958 35
1792672963 35
1792672968 35
1792672973 43
1792672978 43
1792672983 43
1792672988 43
1792672993 43
1792672998 43
1792673003 43
1792673008 43
1792673013 43
1792673018 43
1792673023 43
1792673028 43
1792673033 43
1792673038 43
1792673043 43
1792673048 43
```
</details>

---

