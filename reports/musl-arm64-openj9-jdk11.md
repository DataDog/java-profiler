---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-02 05:32:51 EST

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
| CPU Cores (start) | 14 |
| CPU Cores (end) | 14 |
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
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 11 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (1 unique values: 14-14 cores)</summary>

```
1793615254 14
1793615259 14
1793615264 14
1793615269 14
1793615274 14
1793615279 14
1793615284 14
1793615289 14
1793615294 14
1793615299 14
1793615304 14
1793615309 14
1793615314 14
1793615319 14
1793615324 14
1793615329 14
1793615334 14
1793615339 14
1793615344 14
1793615349 14
```
</details>

---

