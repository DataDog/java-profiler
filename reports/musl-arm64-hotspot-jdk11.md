---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-15 21:12:27 EST

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
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 9 |
| Allocations | 44 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 297 |
| Sample Rate | 4.95/sec |
| Health Score | 309% |
| Threads | 12 |
| Allocations | 99 |

<details>
<summary>CPU Timeline (2 unique values: 35-40 cores)</summary>

```
1794794910 35
1794794915 35
1794794920 35
1794794925 35
1794794930 35
1794794935 35
1794794940 35
1794794945 35
1794794950 35
1794794955 35
1794794960 35
1794794965 35
1794794970 35
1794794975 35
1794794980 35
1794794985 40
1794794990 40
1794794995 40
1794795000 40
1794795005 40
```
</details>

---

