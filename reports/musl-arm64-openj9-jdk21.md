---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-24 08:55:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 11 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 376 |
| Sample Rate | 6.27/sec |
| Health Score | 392% |
| Threads | 12 |
| Allocations | 123 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787575859 64
1787575864 64
1787575869 64
1787575874 64
1787575879 64
1787575884 64
1787575889 64
1787575894 64
1787575899 64
1787575904 64
1787575909 64
1787575914 64
1787575919 64
1787575924 64
1787575929 64
1787575934 64
1787575939 64
1787575944 64
1787575950 64
1787575955 64
```
</details>

---

