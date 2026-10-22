---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-22 13:06:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 260 |
| Sample Rate | 4.33/sec |
| Health Score | 271% |
| Threads | 9 |
| Allocations | 122 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 6 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (2 unique values: 14-22 cores)</summary>

```
1792688449 14
1792688454 14
1792688459 14
1792688464 14
1792688469 22
1792688474 22
1792688479 22
1792688484 22
1792688489 22
1792688494 22
1792688499 22
1792688504 22
1792688509 22
1792688514 22
1792688519 22
1792688524 22
1792688529 22
1792688534 22
1792688539 22
1792688544 22
```
</details>

---

