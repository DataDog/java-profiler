---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-31 00:49:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 7 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 807 |
| Sample Rate | 13.45/sec |
| Health Score | 841% |
| Threads | 9 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (2 unique values: 12-14 cores)</summary>

```
1788151546 14
1788151551 14
1788151556 14
1788151561 14
1788151566 14
1788151571 14
1788151576 14
1788151581 14
1788151586 12
1788151591 12
1788151596 12
1788151601 12
1788151606 12
1788151611 12
1788151616 12
1788151621 12
1788151626 12
1788151631 12
1788151636 14
1788151641 14
```
</details>

---

