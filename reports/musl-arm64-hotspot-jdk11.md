---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-30 11:07:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 8 |
| Allocations | 3 |

<details>
<summary>CPU Timeline (5 unique values: 36-43 cores)</summary>

```
1793372537 42
1793372542 42
1793372547 42
1793372552 42
1793372557 43
1793372562 43
1793372567 42
1793372572 42
1793372577 42
1793372582 42
1793372587 38
1793372592 38
1793372597 38
1793372602 38
1793372607 38
1793372612 38
1793372617 38
1793372622 38
1793372627 38
1793372632 38
```
</details>

---

