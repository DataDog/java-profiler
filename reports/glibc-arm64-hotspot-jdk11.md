---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-07 10:01:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 340 |
| Sample Rate | 5.67/sec |
| Health Score | 354% |
| Threads | 10 |
| Allocations | 164 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 119 |
| Sample Rate | 1.98/sec |
| Health Score | 124% |
| Threads | 16 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1794063459 38
1794063464 38
1794063469 38
1794063474 38
1794063479 38
1794063484 38
1794063489 38
1794063494 38
1794063499 38
1794063504 38
1794063509 38
1794063514 38
1794063519 43
1794063524 43
1794063529 43
1794063534 43
1794063539 43
1794063544 43
1794063549 43
1794063554 43
```
</details>

---

