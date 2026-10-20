---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-20 05:55:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 9 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 253 |
| Sample Rate | 4.22/sec |
| Health Score | 264% |
| Threads | 12 |
| Allocations | 138 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1792489922 43
1792489927 43
1792489933 43
1792489938 43
1792489943 43
1792489948 38
1792489953 38
1792489958 38
1792489963 38
1792489968 38
1792489973 38
1792489978 38
1792489983 38
1792489988 38
1792489993 38
1792489998 38
1792490003 43
1792490008 43
1792490013 43
1792490018 43
```
</details>

---

