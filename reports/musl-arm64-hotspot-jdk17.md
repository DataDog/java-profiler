---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-21 00:57:37 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 214 |
| Sample Rate | 3.57/sec |
| Health Score | 223% |
| Threads | 9 |
| Allocations | 167 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 7 |
| Sample Rate | 0.12/sec |
| Health Score | 8% |
| Threads | 6 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (3 unique values: 24-29 cores)</summary>

```
1789966361 24
1789966366 24
1789966371 24
1789966376 24
1789966381 24
1789966386 24
1789966391 24
1789966396 24
1789966401 24
1789966406 24
1789966411 24
1789966416 29
1789966421 29
1789966426 26
1789966431 26
1789966436 26
1789966441 26
1789966446 26
1789966451 26
1789966456 26
```
</details>

---

