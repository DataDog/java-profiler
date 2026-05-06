---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-06 08:18:45 EDT

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 8 |
| Allocations | 87 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 47 |
| Sample Rate | 0.78/sec |
| Health Score | 49% |
| Threads | 11 |
| Allocations | 76 |

<details>
<summary>CPU Timeline (3 unique values: 55-64 cores)</summary>

```
1778069586 55
1778069591 55
1778069596 55
1778069601 55
1778069606 55
1778069611 55
1778069616 55
1778069621 55
1778069626 55
1778069631 55
1778069636 55
1778069641 55
1778069646 55
1778069651 55
1778069656 55
1778069661 55
1778069666 55
1778069671 60
1778069676 60
1778069681 64
```
</details>

---

