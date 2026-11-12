---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ❌ FAIL

**Date:** 2026-11-12 13:35:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 9 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 85-91 cores)</summary>

```
1794508172 85
1794508178 85
1794508183 85
1794508188 87
1794508193 87
1794508198 87
1794508203 87
1794508208 87
1794508213 87
1794508218 87
1794508223 87
1794508228 87
1794508233 87
1794508238 87
1794508243 87
1794508248 87
1794508253 87
1794508258 87
1794508263 87
1794508268 89
```
</details>

---

