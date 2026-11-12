---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-12 13:37:09 EST

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 381 |
| Sample Rate | 6.35/sec |
| Health Score | 397% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 217 |
| Sample Rate | 3.62/sec |
| Health Score | 226% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 74-79 cores)</summary>

```
1794508163 75
1794508168 75
1794508173 75
1794508178 75
1794508183 75
1794508188 77
1794508193 77
1794508198 79
1794508203 79
1794508208 79
1794508213 79
1794508218 79
1794508223 79
1794508228 79
1794508233 79
1794508238 79
1794508243 79
1794508248 79
1794508253 79
1794508258 79
```
</details>

---

