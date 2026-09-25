---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-25 05:16:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 8 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 15 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (2 unique values: 38-52 cores)</summary>

```
1790327436 52
1790327441 52
1790327446 52
1790327451 52
1790327456 52
1790327461 52
1790327466 52
1790327471 52
1790327476 52
1790327481 52
1790327486 52
1790327491 52
1790327496 52
1790327501 52
1790327506 52
1790327511 52
1790327516 52
1790327521 52
1790327526 52
1790327531 52
```
</details>

---

