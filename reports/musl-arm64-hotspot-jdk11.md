---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 07:26:18 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 8 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 9 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1794572469 43
1794572474 43
1794572479 43
1794572484 43
1794572489 43
1794572494 43
1794572499 43
1794572504 43
1794572509 43
1794572514 43
1794572519 43
1794572524 43
1794572529 38
1794572534 38
1794572539 38
1794572544 38
1794572549 38
1794572554 38
1794572559 38
1794572564 38
```
</details>

---

