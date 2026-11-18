---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 06:38:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 9 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1795001610 29
1795001615 29
1795001620 29
1795001625 29
1795001630 29
1795001635 29
1795001640 34
1795001645 34
1795001650 34
1795001655 34
1795001660 34
1795001665 34
1795001670 34
1795001675 34
1795001680 34
1795001685 34
1795001690 34
1795001695 34
1795001700 34
1795001705 34
```
</details>

---

