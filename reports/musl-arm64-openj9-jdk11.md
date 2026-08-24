---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-24 08:55:32 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 877 |
| Sample Rate | 14.62/sec |
| Health Score | 914% |
| Threads | 8 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1787575867 48
1787575872 48
1787575877 48
1787575882 48
1787575887 48
1787575892 48
1787575897 48
1787575902 48
1787575907 48
1787575912 48
1787575917 48
1787575922 48
1787575927 48
1787575932 48
1787575937 48
1787575942 48
1787575947 48
1787575952 48
1787575957 48
1787575962 48
```
</details>

---

