---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-27 08:24:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 34 |
| Sample Rate | 0.57/sec |
| Health Score | 36% |
| Threads | 11 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795785573 64
1795785578 64
1795785583 64
1795785588 64
1795785593 64
1795785598 64
1795785603 64
1795785608 64
1795785613 64
1795785618 64
1795785623 64
1795785628 64
1795785633 64
1795785639 64
1795785644 64
1795785649 64
1795785654 64
1795785659 64
1795785664 64
1795785669 64
```
</details>

---

