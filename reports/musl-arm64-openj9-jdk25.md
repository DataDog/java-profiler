---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-13 01:03:53 EDT

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 226 |
| Sample Rate | 3.77/sec |
| Health Score | 236% |
| Threads | 10 |
| Allocations | 165 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (2 unique values: 30-35 cores)</summary>

```
1791867569 35
1791867574 35
1791867579 35
1791867584 30
1791867589 30
1791867594 30
1791867599 30
1791867604 30
1791867609 30
1791867614 30
1791867619 30
1791867624 30
1791867629 30
1791867634 30
1791867639 30
1791867644 30
1791867649 30
1791867654 30
1791867659 30
1791867664 30
```
</details>

---

