---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-23 16:04:37 EDT

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
| CPU Cores (start) | 90 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 388 |
| Sample Rate | 6.47/sec |
| Health Score | 404% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 10 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (3 unique values: 83-92 cores)</summary>

```
1792785519 90
1792785524 90
1792785529 90
1792785534 90
1792785539 90
1792785544 90
1792785549 90
1792785554 90
1792785559 90
1792785564 90
1792785569 90
1792785574 92
1792785579 92
1792785584 92
1792785589 92
1792785594 92
1792785599 92
1792785604 83
1792785609 83
1792785614 83
```
</details>

---

