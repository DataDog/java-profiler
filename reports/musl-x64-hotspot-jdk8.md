---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-22 19:06:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 159 |
| Sample Rate | 2.65/sec |
| Health Score | 166% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 279 |
| Sample Rate | 4.65/sec |
| Health Score | 291% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 10-30 cores)</summary>

```
1792710071 30
1792710076 30
1792710081 30
1792710086 10
1792710091 10
1792710096 12
1792710101 12
1792710106 12
1792710111 12
1792710116 12
1792710121 12
1792710126 12
1792710131 12
1792710136 12
1792710141 12
1792710146 12
1792710151 12
1792710156 12
1792710161 12
1792710166 12
```
</details>

---

