---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-12 02:56:28 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 12 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 12 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (2 unique values: 47-52 cores)</summary>

```
1778568619 47
1778568624 47
1778568629 47
1778568634 47
1778568639 47
1778568644 52
1778568649 52
1778568654 52
1778568659 52
1778568664 52
1778568669 52
1778568674 52
1778568679 52
1778568684 52
1778568690 52
1778568695 52
1778568700 52
1778568705 52
1778568710 52
1778568715 52
```
</details>

---

