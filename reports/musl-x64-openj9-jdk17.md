---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-23 16:04:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 568 |
| Sample Rate | 9.47/sec |
| Health Score | 592% |
| Threads | 11 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1792785509 94
1792785514 94
1792785519 96
1792785524 96
1792785529 96
1792785534 96
1792785539 96
1792785544 96
1792785549 96
1792785554 96
1792785559 96
1792785564 96
1792785569 96
1792785574 96
1792785579 96
1792785584 96
1792785589 96
1792785594 96
1792785599 96
1792785604 96
```
</details>

---

