---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-23 16:04:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 447 |
| Sample Rate | 7.45/sec |
| Health Score | 466% |
| Threads | 8 |
| Allocations | 325 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 9 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1792785595 30
1792785600 30
1792785605 32
1792785610 32
1792785615 32
1792785620 32
1792785625 32
1792785630 32
1792785635 32
1792785640 32
1792785645 32
1792785650 32
1792785655 32
1792785660 32
1792785665 32
1792785670 32
1792785675 32
1792785680 32
1792785685 32
1792785690 32
```
</details>

---

