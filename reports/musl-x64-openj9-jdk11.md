---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 13:37:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 8 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 822 |
| Sample Rate | 13.70/sec |
| Health Score | 856% |
| Threads | 10 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (4 unique values: 76-83 cores)</summary>

```
1794508167 78
1794508172 76
1794508177 76
1794508182 76
1794508187 76
1794508192 76
1794508198 76
1794508203 76
1794508208 76
1794508213 76
1794508218 76
1794508223 80
1794508228 80
1794508233 80
1794508238 80
1794508243 80
1794508248 80
1794508253 80
1794508258 80
1794508263 80
```
</details>

---

