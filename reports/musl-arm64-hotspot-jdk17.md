---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ❌ FAIL

**Date:** 2026-11-17 05:23:19 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 32 |
| Sample Rate | 0.53/sec |
| Health Score | 33% |
| Threads | 12 |
| Allocations | 27 |

<details>
<summary>CPU Timeline (1 unique values: 38-38 cores)</summary>

```
1794910611 38
1794910616 38
1794910621 38
1794910626 38
1794910631 38
1794910636 38
1794910641 38
1794910646 38
1794910651 38
1794910656 38
1794910661 38
1794910666 38
1794910671 38
1794910676 38
1794910681 38
1794910686 38
1794910691 38
1794910696 38
1794910701 38
1794910706 38
```
</details>

---

