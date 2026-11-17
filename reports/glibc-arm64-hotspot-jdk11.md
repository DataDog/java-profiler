---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-17 16:21:35 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
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
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 11 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1051 |
| Sample Rate | 17.52/sec |
| Health Score | 1095% |
| Threads | 10 |
| Allocations | 463 |

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
1794950159 46
1794950164 46
1794950169 46
1794950174 46
1794950179 51
1794950184 51
1794950189 51
1794950194 51
1794950199 51
1794950204 51
1794950209 51
1794950214 51
1794950219 51
```
</details>

---

