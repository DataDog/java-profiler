---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-25 00:58:50 EDT

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 209 |
| Sample Rate | 3.48/sec |
| Health Score | 217% |
| Threads | 11 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 13 |
| Allocations | 185 |

<details>
<summary>CPU Timeline (2 unique values: 22-27 cores)</summary>

```
1790312054 22
1790312059 22
1790312064 22
1790312069 27
1790312074 27
1790312079 27
1790312084 27
1790312089 27
1790312094 27
1790312099 27
1790312104 27
1790312109 27
1790312114 27
1790312119 27
1790312124 27
1790312129 27
1790312134 27
1790312139 27
1790312144 27
1790312149 27
```
</details>

---

