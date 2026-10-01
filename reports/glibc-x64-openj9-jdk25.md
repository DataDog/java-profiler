---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-01 08:19:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 380 |
| Sample Rate | 6.33/sec |
| Health Score | 396% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 600 |
| Sample Rate | 10.00/sec |
| Health Score | 625% |
| Threads | 11 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (4 unique values: 61-94 cores)</summary>

```
1790856873 61
1790856878 61
1790856883 63
1790856888 63
1790856893 63
1790856898 63
1790856903 63
1790856908 63
1790856913 65
1790856918 65
1790856923 65
1790856928 65
1790856933 65
1790856938 65
1790856943 65
1790856948 65
1790856953 65
1790856958 63
1790856963 63
1790856968 94
```
</details>

---

