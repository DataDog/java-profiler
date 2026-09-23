---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-23 07:03:22 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 614 |
| Sample Rate | 10.23/sec |
| Health Score | 639% |
| Threads | 8 |
| Allocations | 329 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 7 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1790161198 64
1790161203 64
1790161208 64
1790161213 64
1790161218 64
1790161223 64
1790161228 64
1790161233 64
1790161238 64
1790161243 64
1790161248 64
1790161253 64
1790161258 64
1790161263 64
1790161268 64
1790161273 64
1790161278 64
1790161283 64
1790161288 64
1790161293 64
```
</details>

---

