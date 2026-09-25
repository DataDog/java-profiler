---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-25 00:58:50 EDT

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 14 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (2 unique values: 22-59 cores)</summary>

```
1790312059 22
1790312064 22
1790312069 22
1790312074 22
1790312079 22
1790312084 22
1790312089 22
1790312094 22
1790312099 22
1790312104 22
1790312109 22
1790312114 22
1790312119 22
1790312124 59
1790312129 59
1790312134 59
1790312139 59
1790312144 59
1790312149 59
1790312154 22
```
</details>

---

