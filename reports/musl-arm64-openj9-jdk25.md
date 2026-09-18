---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-18 07:49:59 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 168 |
| Sample Rate | 2.80/sec |
| Health Score | 175% |
| Threads | 14 |
| Allocations | 85 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789731832 48
1789731837 48
1789731842 43
1789731847 43
1789731852 43
1789731857 43
1789731862 43
1789731867 43
1789731872 43
1789731877 43
1789731882 43
1789731887 43
1789731892 43
1789731897 48
1789731902 48
1789731907 48
1789731912 48
1789731917 48
1789731922 48
1789731927 48
```
</details>

---

