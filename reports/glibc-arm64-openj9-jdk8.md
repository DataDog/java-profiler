---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-11 05:49:16 EDT

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 12 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 56-64 cores)</summary>

```
1786441484 56
1786441489 56
1786441494 56
1786441499 56
1786441504 56
1786441509 56
1786441514 56
1786441519 56
1786441524 56
1786441529 56
1786441534 56
1786441539 56
1786441544 56
1786441549 64
1786441554 64
1786441559 64
1786441564 64
1786441569 64
1786441574 64
1786441579 64
```
</details>

---

