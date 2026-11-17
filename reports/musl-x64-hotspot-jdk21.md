---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-17 06:25:18 EST

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 9 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 887 |
| Sample Rate | 14.78/sec |
| Health Score | 924% |
| Threads | 11 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (4 unique values: 86-94 cores)</summary>

```
1794914409 86
1794914414 86
1794914419 86
1794914424 86
1794914429 86
1794914434 86
1794914439 86
1794914444 86
1794914450 86
1794914455 86
1794914460 88
1794914465 88
1794914470 88
1794914475 88
1794914480 88
1794914485 88
1794914490 88
1794914495 88
1794914500 91
1794914505 91
```
</details>

---

