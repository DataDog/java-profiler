---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-10 16:31:53 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 287 |
| Sample Rate | 4.78/sec |
| Health Score | 299% |
| Threads | 9 |
| Allocations | 160 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 130 |
| Sample Rate | 2.17/sec |
| Health Score | 136% |
| Threads | 10 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (2 unique values: 53-64 cores)</summary>

```
1786393546 53
1786393551 53
1786393556 64
1786393561 64
1786393566 64
1786393571 64
1786393576 64
1786393581 64
1786393586 64
1786393591 64
1786393596 64
1786393601 64
1786393606 64
1786393611 64
1786393616 64
1786393621 64
1786393626 64
1786393631 64
1786393636 64
1786393641 64
```
</details>

---

