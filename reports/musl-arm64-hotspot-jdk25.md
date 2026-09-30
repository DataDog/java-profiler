---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-30 15:17:26 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 12 |
| Allocations | 43 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 145 |
| Sample Rate | 2.42/sec |
| Health Score | 151% |
| Threads | 14 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790795583 48
1790795588 48
1790795593 48
1790795598 48
1790795603 48
1790795608 48
1790795613 43
1790795618 43
1790795623 43
1790795628 43
1790795633 43
1790795638 43
1790795643 43
1790795648 43
1790795653 43
1790795658 43
1790795663 43
1790795668 43
1790795673 43
1790795678 48
```
</details>

---

