---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-20 05:55:28 EDT

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
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 11 |
| Allocations | 171 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792489862 48
1792489867 48
1792489872 48
1792489877 48
1792489882 43
1792489887 43
1792489892 43
1792489898 43
1792489903 43
1792489908 43
1792489913 43
1792489918 43
1792489923 43
1792489928 43
1792489933 48
1792489938 48
1792489943 48
1792489948 48
1792489953 48
1792489958 48
```
</details>

---

