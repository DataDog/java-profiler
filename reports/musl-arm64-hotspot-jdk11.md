---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-22 19:06:02 EDT

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
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 12 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1792710138 46
1792710143 46
1792710148 46
1792710153 46
1792710158 46
1792710163 46
1792710168 46
1792710173 46
1792710178 46
1792710183 46
1792710188 46
1792710193 46
1792710198 46
1792710203 46
1792710208 46
1792710213 51
1792710218 51
1792710223 51
1792710228 51
1792710233 51
```
</details>

---

