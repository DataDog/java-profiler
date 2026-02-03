---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-03 08:38:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 762 |
| Sample Rate | 12.70/sec |
| Health Score | 794% |
| Threads | 10 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1014 |
| Sample Rate | 16.90/sec |
| Health Score | 1056% |
| Threads | 11 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (4 unique values: 26-32 cores)</summary>

```
1770125693 29
1770125698 29
1770125703 29
1770125708 29
1770125713 29
1770125718 29
1770125723 29
1770125728 29
1770125733 29
1770125738 32
1770125743 32
1770125748 29
1770125753 29
1770125758 29
1770125763 29
1770125768 29
1770125773 29
1770125778 27
1770125783 27
1770125788 27
```
</details>

---

