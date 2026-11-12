---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-12 13:37:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 89 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 203 |
| Sample Rate | 3.38/sec |
| Health Score | 211% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 207 |
| Sample Rate | 3.45/sec |
| Health Score | 216% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 87-93 cores)</summary>

```
1794508162 89
1794508167 87
1794508172 87
1794508177 87
1794508182 87
1794508188 89
1794508193 89
1794508198 89
1794508203 89
1794508208 89
1794508213 89
1794508218 89
1794508223 89
1794508228 89
1794508233 89
1794508238 91
1794508243 91
1794508248 91
1794508253 91
1794508258 91
```
</details>

---

