---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 06:38:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 10 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 11 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1795001625 34
1795001630 34
1795001635 29
1795001640 29
1795001645 29
1795001650 29
1795001655 29
1795001660 29
1795001665 29
1795001670 29
1795001675 29
1795001680 29
1795001685 29
1795001690 29
1795001695 29
1795001700 29
1795001705 29
1795001710 29
1795001715 29
1795001720 29
```
</details>

---

