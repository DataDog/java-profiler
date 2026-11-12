---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 13:35:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 307 |
| Sample Rate | 5.12/sec |
| Health Score | 320% |
| Threads | 10 |
| Allocations | 114 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 372 |
| Sample Rate | 6.20/sec |
| Health Score | 388% |
| Threads | 14 |
| Allocations | 136 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794508148 43
1794508153 43
1794508158 43
1794508163 43
1794508168 43
1794508173 43
1794508178 43
1794508183 43
1794508188 43
1794508193 48
1794508198 48
1794508203 43
1794508208 43
1794508213 43
1794508218 43
1794508223 43
1794508228 43
1794508233 43
1794508238 43
1794508243 43
```
</details>

---

