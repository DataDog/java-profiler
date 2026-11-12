---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ❌ FAIL

**Date:** 2026-11-12 13:37:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 9 |
| Allocations | 416 |

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
<summary>CPU Timeline (2 unique values: 85-87 cores)</summary>

```
1794508157 87
1794508162 87
1794508167 87
1794508172 87
1794508177 87
1794508182 87
1794508187 87
1794508192 87
1794508197 87
1794508203 87
1794508208 87
1794508213 87
1794508218 87
1794508223 85
1794508228 85
1794508233 85
1794508238 87
1794508243 87
1794508248 85
1794508253 85
```
</details>

---

