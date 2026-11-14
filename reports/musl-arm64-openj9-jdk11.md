---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-14 06:23:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 444 |
| Sample Rate | 7.40/sec |
| Health Score | 462% |
| Threads | 8 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 9 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (2 unique values: 21-26 cores)</summary>

```
1794655178 26
1794655183 26
1794655188 26
1794655193 26
1794655198 26
1794655203 26
1794655208 26
1794655213 26
1794655218 26
1794655223 26
1794655228 21
1794655233 21
1794655238 21
1794655243 21
1794655248 21
1794655253 21
1794655258 21
1794655263 21
1794655268 21
1794655273 21
```
</details>

---

