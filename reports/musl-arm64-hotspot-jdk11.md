---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 09:46:15 EST

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
| CPU Samples | 146 |
| Sample Rate | 2.43/sec |
| Health Score | 152% |
| Threads | 11 |
| Allocations | 83 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 34 |
| Sample Rate | 0.57/sec |
| Health Score | 36% |
| Threads | 10 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794408092 46
1794408097 46
1794408102 46
1794408107 46
1794408112 46
1794408117 46
1794408122 46
1794408127 46
1794408132 46
1794408137 46
1794408142 46
1794408147 46
1794408152 46
1794408157 51
1794408162 51
1794408167 51
1794408172 51
1794408177 51
1794408182 51
1794408187 51
```
</details>

---

