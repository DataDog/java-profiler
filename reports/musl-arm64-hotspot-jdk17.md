---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-19 05:55:47 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 353 |
| Sample Rate | 5.88/sec |
| Health Score | 368% |
| Threads | 12 |
| Allocations | 104 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1792403474 43
1792403479 43
1792403484 43
1792403489 43
1792403494 43
1792403499 43
1792403504 43
1792403509 43
1792403514 43
1792403519 43
1792403524 43
1792403529 38
1792403534 38
1792403539 38
1792403544 38
1792403549 38
1792403554 38
1792403560 38
1792403565 38
1792403570 38
```
</details>

---

