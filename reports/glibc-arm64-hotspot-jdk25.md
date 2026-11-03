---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-02 21:59:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 12 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (2 unique values: 41-52 cores)</summary>

```
1793674491 41
1793674496 41
1793674501 41
1793674506 41
1793674511 52
1793674516 52
1793674521 52
1793674526 52
1793674531 52
1793674536 52
1793674541 52
1793674546 52
1793674551 52
1793674556 52
1793674561 52
1793674566 52
1793674571 52
1793674576 52
1793674581 52
1793674586 52
```
</details>

---

