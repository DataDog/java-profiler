---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-24 15:41:52 EDT

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 8 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 10 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (2 unique values: 47-52 cores)</summary>

```
1790278645 52
1790278650 52
1790278655 52
1790278660 47
1790278665 47
1790278670 47
1790278675 47
1790278680 47
1790278685 47
1790278690 47
1790278695 47
1790278700 47
1790278705 47
1790278710 52
1790278715 52
1790278720 52
1790278725 52
1790278730 52
1790278735 52
1790278740 52
```
</details>

---

