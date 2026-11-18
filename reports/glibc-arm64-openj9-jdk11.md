---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 05:59:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 12 |
| Allocations | 75 |

<details>
<summary>CPU Timeline (1 unique values: 15-15 cores)</summary>

```
1794999214 15
1794999219 15
1794999224 15
1794999229 15
1794999234 15
1794999239 15
1794999244 15
1794999249 15
1794999254 15
1794999259 15
1794999264 15
1794999269 15
1794999274 15
1794999279 15
1794999284 15
1794999289 15
1794999294 15
1794999299 15
1794999304 15
1794999309 15
```
</details>

---

