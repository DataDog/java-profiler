---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 14:54:00 EST

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
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 11 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 345 |
| Sample Rate | 5.75/sec |
| Health Score | 359% |
| Threads | 11 |
| Allocations | 172 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794340164 46
1794340169 46
1794340174 46
1794340179 46
1794340184 46
1794340189 46
1794340194 46
1794340199 46
1794340204 46
1794340209 46
1794340214 46
1794340219 46
1794340224 46
1794340229 46
1794340234 51
1794340239 51
1794340244 51
1794340249 51
1794340254 51
1794340259 51
```
</details>

---

