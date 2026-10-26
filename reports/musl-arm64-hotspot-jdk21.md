---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-26 07:41:00 EDT

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
| CPU Cores (start) | 20 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 11 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 22 |
| Sample Rate | 0.37/sec |
| Health Score | 23% |
| Threads | 10 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (2 unique values: 20-28 cores)</summary>

```
1793014546 20
1793014551 20
1793014556 20
1793014561 20
1793014566 20
1793014571 20
1793014576 20
1793014581 20
1793014586 20
1793014591 20
1793014596 20
1793014601 20
1793014606 20
1793014611 20
1793014616 20
1793014621 20
1793014626 20
1793014631 20
1793014636 28
1793014641 28
```
</details>

---

