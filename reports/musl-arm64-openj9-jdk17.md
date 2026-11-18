---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 10:07:55 EST

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 14 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (3 unique values: 26-46 cores)</summary>

```
1795014164 26
1795014169 26
1795014174 26
1795014179 26
1795014184 26
1795014189 26
1795014194 26
1795014199 26
1795014204 26
1795014209 26
1795014214 26
1795014219 26
1795014224 26
1795014229 26
1795014234 26
1795014239 46
1795014244 46
1795014249 33
1795014254 33
1795014259 33
```
</details>

---

