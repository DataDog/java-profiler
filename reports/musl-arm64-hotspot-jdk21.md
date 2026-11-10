---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-10 15:03:07 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 11 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 31 |
| Sample Rate | 0.52/sec |
| Health Score | 32% |
| Threads | 12 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794340531 51
1794340536 51
1794340541 51
1794340546 51
1794340551 51
1794340556 46
1794340561 46
1794340566 46
1794340571 46
1794340576 46
1794340581 46
1794340586 46
1794340591 46
1794340596 46
1794340601 46
1794340606 46
1794340611 46
1794340616 46
1794340621 46
1794340626 51
```
</details>

---

