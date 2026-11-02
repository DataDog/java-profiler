---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-02 05:30:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
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
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 33 |
| Sample Rate | 0.55/sec |
| Health Score | 34% |
| Threads | 12 |
| Allocations | 27 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1793615208 64
1793615213 64
1793615218 64
1793615223 64
1793615228 64
1793615233 64
1793615238 64
1793615244 64
1793615249 64
1793615254 64
1793615259 64
1793615264 64
1793615269 64
1793615274 64
1793615279 64
1793615284 64
1793615289 64
1793615294 64
1793615299 64
1793615304 64
```
</details>

---

