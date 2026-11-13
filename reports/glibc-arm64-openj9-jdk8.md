---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-13 07:26:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 143 |
| Sample Rate | 2.38/sec |
| Health Score | 149% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 31-43 cores)</summary>

```
1794572523 43
1794572528 43
1794572533 43
1794572538 31
1794572543 31
1794572548 31
1794572553 31
1794572558 31
1794572563 31
1794572568 31
1794572573 31
1794572578 31
1794572583 31
1794572588 31
1794572593 31
1794572598 31
1794572603 31
1794572608 31
1794572613 31
1794572618 31
```
</details>

---

