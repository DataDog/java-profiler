---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-30 07:31:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 93 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 695 |
| Sample Rate | 11.58/sec |
| Health Score | 724% |
| Threads | 10 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (3 unique values: 91-94 cores)</summary>

```
1790767600 93
1790767605 93
1790767610 93
1790767615 93
1790767620 93
1790767625 91
1790767630 91
1790767635 91
1790767640 91
1790767645 91
1790767650 94
1790767655 94
1790767660 94
1790767665 94
1790767670 94
1790767675 94
1790767680 94
1790767685 94
1790767690 94
1790767695 94
```
</details>

---

