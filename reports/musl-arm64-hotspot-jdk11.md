---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-17 16:21:37 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 11 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 38 |
| Sample Rate | 0.63/sec |
| Health Score | 39% |
| Threads | 11 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794950124 46
1794950129 46
1794950134 46
1794950139 46
1794950144 46
1794950149 46
1794950154 46
1794950160 46
1794950165 46
1794950170 46
1794950175 46
1794950180 51
1794950185 51
1794950190 51
1794950195 51
1794950200 51
1794950205 51
1794950210 51
1794950215 51
1794950220 51
```
</details>

---

