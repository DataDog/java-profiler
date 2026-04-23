---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-23 10:22:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 821 |
| Sample Rate | 13.68/sec |
| Health Score | 855% |
| Threads | 10 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (5 unique values: 21-32 cores)</summary>

```
1776953712 30
1776953717 30
1776953722 32
1776953727 32
1776953732 32
1776953737 32
1776953742 32
1776953747 32
1776953752 32
1776953757 32
1776953762 32
1776953767 32
1776953772 32
1776953777 32
1776953782 25
1776953787 25
1776953792 25
1776953797 23
1776953802 23
1776953807 23
```
</details>

---

