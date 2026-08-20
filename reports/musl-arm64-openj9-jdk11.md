---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-20 05:42:40 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 7 |
| Allocations | 47 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 13 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (2 unique values: 40-47 cores)</summary>

```
1787218622 47
1787218627 47
1787218632 47
1787218637 47
1787218642 47
1787218647 47
1787218652 47
1787218657 47
1787218662 40
1787218667 40
1787218672 40
1787218677 40
1787218682 40
1787218687 40
1787218692 40
1787218697 40
1787218702 40
1787218707 40
1787218712 40
1787218717 40
```
</details>

---

