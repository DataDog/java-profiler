---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-12 14:47:37 EST

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 8 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 296 |
| Sample Rate | 4.93/sec |
| Health Score | 308% |
| Threads | 13 |
| Allocations | 119 |

<details>
<summary>CPU Timeline (2 unique values: 35-47 cores)</summary>

```
1794512573 35
1794512578 47
1794512583 47
1794512588 47
1794512593 47
1794512598 47
1794512603 47
1794512608 47
1794512613 47
1794512618 47
1794512623 47
1794512628 47
1794512633 47
1794512639 47
1794512644 47
1794512649 47
1794512654 47
1794512659 47
1794512664 47
1794512669 47
```
</details>

---

