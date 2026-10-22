---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-22 13:25:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 403 |
| Sample Rate | 6.72/sec |
| Health Score | 420% |
| Threads | 11 |
| Allocations | 155 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 12 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (3 unique values: 51-64 cores)</summary>

```
1792689568 51
1792689573 64
1792689578 64
1792689583 64
1792689588 64
1792689593 64
1792689598 64
1792689603 64
1792689608 64
1792689613 64
1792689618 64
1792689623 64
1792689628 64
1792689633 64
1792689638 64
1792689643 64
1792689649 64
1792689654 64
1792689659 64
1792689664 64
```
</details>

---

