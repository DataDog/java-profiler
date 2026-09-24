---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-24 07:03:17 EDT

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 470 |
| Sample Rate | 7.83/sec |
| Health Score | 489% |
| Threads | 8 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 666 |
| Sample Rate | 11.10/sec |
| Health Score | 694% |
| Threads | 10 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (2 unique values: 22-32 cores)</summary>

```
1790247550 22
1790247555 22
1790247560 22
1790247565 22
1790247570 22
1790247575 22
1790247580 22
1790247585 22
1790247590 22
1790247595 22
1790247600 22
1790247605 22
1790247610 22
1790247615 22
1790247620 22
1790247625 22
1790247630 22
1790247635 32
1790247640 32
1790247645 32
```
</details>

---

