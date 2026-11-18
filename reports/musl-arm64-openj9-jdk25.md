---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 10:07:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 262 |
| Sample Rate | 4.37/sec |
| Health Score | 273% |
| Threads | 11 |
| Allocations | 156 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 13 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1795014164 48
1795014169 48
1795014174 48
1795014179 48
1795014184 48
1795014189 43
1795014194 43
1795014199 43
1795014204 43
1795014209 43
1795014214 43
1795014219 43
1795014224 43
1795014229 43
1795014234 43
1795014239 43
1795014244 43
1795014249 43
1795014254 43
1795014259 48
```
</details>

---

