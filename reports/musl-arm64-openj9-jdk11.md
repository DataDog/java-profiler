---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-17 09:07:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 135 |
| Sample Rate | 2.25/sec |
| Health Score | 141% |
| Threads | 8 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 10 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (2 unique values: 63-64 cores)</summary>

```
1786971685 63
1786971690 63
1786971695 64
1786971700 64
1786971705 64
1786971710 64
1786971715 64
1786971720 64
1786971725 64
1786971730 64
1786971735 64
1786971740 64
1786971745 64
1786971750 64
1786971755 64
1786971760 64
1786971765 64
1786971770 64
1786971775 64
1786971780 64
```
</details>

---

