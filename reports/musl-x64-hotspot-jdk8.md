---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-13 07:27:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 178 |
| Sample Rate | 2.97/sec |
| Health Score | 186% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 280 |
| Sample Rate | 4.67/sec |
| Health Score | 292% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 14-30 cores)</summary>

```
1794572468 16
1794572473 16
1794572479 16
1794572484 16
1794572489 16
1794572494 16
1794572499 16
1794572504 16
1794572509 16
1794572514 16
1794572519 16
1794572524 16
1794572529 16
1794572534 16
1794572539 14
1794572544 14
1794572549 14
1794572554 14
1794572559 14
1794572564 14
```
</details>

---

