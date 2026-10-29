---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-29 09:35:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 11 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (4 unique values: 58-61 cores)</summary>

```
1793280646 60
1793280651 60
1793280656 60
1793280661 60
1793280666 60
1793280671 60
1793280676 60
1793280681 60
1793280686 60
1793280691 60
1793280696 60
1793280701 60
1793280706 58
1793280711 58
1793280717 58
1793280722 58
1793280727 58
1793280732 58
1793280737 58
1793280742 58
```
</details>

---

