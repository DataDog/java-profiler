---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-03 11:22:16 EST

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 9 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 12 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (2 unique values: 37-40 cores)</summary>

```
1793722626 40
1793722631 40
1793722636 40
1793722641 40
1793722646 40
1793722651 40
1793722656 40
1793722661 40
1793722666 40
1793722671 40
1793722676 40
1793722681 40
1793722686 40
1793722691 40
1793722696 40
1793722701 40
1793722706 40
1793722711 40
1793722716 40
1793722721 40
```
</details>

---

