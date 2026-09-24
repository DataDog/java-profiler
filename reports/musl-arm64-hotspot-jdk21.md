---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-24 05:24:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 8 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 187 |
| Sample Rate | 3.12/sec |
| Health Score | 195% |
| Threads | 11 |
| Allocations | 171 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1790241513 46
1790241518 46
1790241523 46
1790241528 46
1790241533 46
1790241538 46
1790241543 46
1790241548 46
1790241553 46
1790241558 46
1790241563 46
1790241568 46
1790241573 48
1790241578 48
1790241584 48
1790241589 48
1790241594 48
1790241599 48
1790241604 43
1790241609 43
```
</details>

---

