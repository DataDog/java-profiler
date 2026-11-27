---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ❌ FAIL

**Date:** 2026-11-27 14:05:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
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
| CPU Samples | 26 |
| Sample Rate | 0.43/sec |
| Health Score | 27% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 1 |
| Sample Rate | 0.02/sec |
| Health Score | 1% |
| Threads | 1 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795806071 64
1795806076 64
1795806081 64
1795806086 64
1795806091 64
1795806096 64
1795806101 64
1795806106 64
1795806111 64
1795806116 64
1795806121 64
1795806126 64
1795806131 64
1795806136 64
1795806141 64
1795806146 64
1795806151 64
1795806156 64
1795806161 64
1795806166 64
```
</details>

---

