---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-23 16:42:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 718 |
| Sample Rate | 11.97/sec |
| Health Score | 748% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 997 |
| Sample Rate | 16.62/sec |
| Health Score | 1039% |
| Threads | 11 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (2 unique values: 86-87 cores)</summary>

```
1790195842 87
1790195847 87
1790195852 87
1790195857 86
1790195862 86
1790195867 86
1790195872 86
1790195877 86
1790195882 86
1790195887 86
1790195892 86
1790195897 86
1790195902 86
1790195907 86
1790195912 86
1790195917 86
1790195922 86
1790195927 87
1790195932 87
1790195937 87
```
</details>

---

